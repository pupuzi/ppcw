#include <winsock2.h>
#include "event2/http.h"
#include "event2/event.h"
#include "callback.h"
#include "parse.h"

int main(int argc, char* argv[])
{
	if (argc < g_tarServerConfig.m_nSize)
	{
		printf("Service startup failure!");
		return 0;
	}
	
	CheckArgv(argv);

	//g_tarServerConfig.m_strIP = "192.168.1.251";
	//g_tarServerConfig.m_strPort = "8060";
	//g_tarServerConfig.m_strDownloadPath = "D:";
	//g_tarServerConfig.m_strUploadPath = "D:";

	printf("服务器IP[%s]\n", g_tarServerConfig.m_strIP.c_str());
	printf("服务器端口[%s]\n", g_tarServerConfig.m_strPort.c_str());
	printf("下载路径根节点[%s]\n", g_tarServerConfig.m_strDownloadPath.c_str());
	printf("上传路径根节点[%s]\n", g_tarServerConfig.m_strUploadPath.c_str());

	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);

	struct event_base* base;
	struct evhttp* http;

	base = event_base_new();
	if (!base) {
		fprintf(stderr, "Couldn't create an event_base!\n");
		return 0;
	}

	http = evhttp_new(base);
	if (!http) {
		fprintf(stderr, "Couldn't create evhttp!\n");
		return 0;
	}

	ev_uint16_t port = stol(g_tarServerConfig.m_strPort);
	evhttp_bind_socket(http, g_tarServerConfig.m_strIP.c_str(), port);
	evhttp_set_gencb(http, http_request_cb, NULL);

	printf("服务启动成功!\n");

	event_base_dispatch(base);
	evhttp_free(http);

	return 0;
}