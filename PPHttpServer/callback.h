#pragma once
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <corecrt_io.h>
#include "event2/buffer.h"
#include "event2/buffer_compat.h"
#include "server.h"

void PrintfLogs(const char* strLogs)
{
	SYSTEMTIME tm;
	GetSystemTime(&tm);
	printf("[%d-%d-%d %d:%d:%d]: %s \n",tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, strLogs);
}

void SendFile(evhttp_request* pReq, int nCode, int nfd, long long nSize)
{
	struct evbuffer* outBuf;
	outBuf = evbuffer_new();
	evbuffer_add_file(outBuf, nfd, 0, nSize);
	evhttp_send_reply(pReq, nCode, std::to_string(nCode).c_str(), outBuf);
	evbuffer_free(outBuf);
}

void SendReply(evhttp_request* pReq, int nCode, const char* strLogs)
{
	struct evbuffer* outBuf;
	outBuf = evbuffer_new();
	evbuffer_add_printf(outBuf, "%s", strLogs);
	evhttp_send_reply(pReq, nCode, std::to_string(nCode).c_str(), outBuf);
	evbuffer_free(outBuf);
}

long GetBufferData(evbuffer* pInput)
{
	//确定该数据块的分隔符字符串
	evbuffer_lock(pInput);
	char* strHeader = evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);
	long nLen = strlen(strHeader);
	evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);
	evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);
	evbuffer_readln(pInput, 0, EVBUFFER_EOL_CRLF);

	long nOutputLen = EVBUFFER_LENGTH(pInput) - nLen - 6;

	evbuffer_unlock(pInput);
	return nOutputLen;
}

std::string GetFileName(unsigned char* pszData)
{
	std::string strData = (char*)pszData;
	//查询filename
	const char* filename = "filename=\"";
	long nFilename = strlen(filename);
	std::string strName = strData.substr(strData.find(filename) + nFilename);
	strName = strName.substr(0, strName.find('\"'));
	return strName;
}

int InitFileFd(const char* strPath)
{
	int fd = 0;
	std::string strFilePath = g_tarServerConfig.m_strDownloadPath + strPath;
	_sopen_s(&fd, strFilePath.c_str(), O_RDONLY | O_BINARY, _SH_DENYWR, _S_IREAD);
	return fd;
}

void http_request_cb(struct evhttp_request* request, void* arg)
{
	evhttp_cmd_type nType = evhttp_request_get_command(request);
	if (nType == EVHTTP_REQ_GET)
	{
		const evhttp_uri* url = evhttp_request_get_evhttp_uri(request);
		const char* strPath = evhttp_uri_get_path(url);
		const char* pQuery = evhttp_uri_get_query(url);
		const char* strHost = evhttp_request_get_host(request);

		int fd = InitFileFd(strPath);
		if (fd < 0)
		{
			SendReply(request, HTTP_NOTFOUND, NULL);
			PrintfLogs("Download error: file not found!");
			return;
		}

		struct stat st;
		if (fstat(fd, &st) < 0)
		{
			SendReply(request, HTTP_NOTFOUND, "file: not found!");
			PrintfLogs("Download error: file not found!");
		}
		else
		{
			SendFile(request, HTTP_OK, fd, st.st_size);
			std::string strLogs = std::string(g_tarServerConfig.m_strDownloadPath) + std::string(strPath) + " download success!";
			PrintfLogs(strLogs.c_str());
		}
	}
	else if (nType == EVHTTP_REQ_POST)
	{
		const evhttp_uri* url = evhttp_request_get_evhttp_uri(request);
		const char* strPath = evhttp_uri_get_path(url);
		const char* strHost = evhttp_request_get_host(request);

		evbuffer* pInput = evhttp_request_get_input_buffer(request);

		long nLen = EVBUFFER_LENGTH(pInput);
		unsigned char* strData = EVBUFFER_DATA(pInput);
		strData[nLen] = '\0';

		std::string strName = GetFileName(strData);
		std::string strFilePath = g_tarServerConfig.m_strUploadPath + strPath + strName;

		FILE* fp = NULL;
		fopen_s(&fp, strFilePath.c_str(), "wb");

		if (fp != NULL)
		{
			long nOutputLen = GetBufferData(pInput);
			fwrite(EVBUFFER_DATA(pInput), 1, nOutputLen, fp);
			fclose(fp);
			SendReply(request, HTTP_OK, NULL);
			std::string strLogs = strFilePath + " upload success!";
			PrintfLogs(strLogs.c_str());
		}
		else
		{
			SendReply(request, HTTP_NOTFOUND, NULL);
			
			PrintfLogs("Upload error: path not found!");
		}
	}
	else
	{
		SendReply(request, HTTP_BADMETHOD, "method: not allowed!");
		PrintfLogs("Upload error: method not allowed!");
	}
}