#pragma once
#include <string>

struct http_server_config 
{
	long m_nSize = 5;
	std::string m_strCmdName;
	std::string m_strIP;
	std::string m_strPort;
	std::string m_strDownloadPath;
	std::string m_strUploadPath;
};

static http_server_config g_tarServerConfig;