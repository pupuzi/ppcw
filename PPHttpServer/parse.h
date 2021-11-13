#pragma once

#include "server.h"

void CheckArgv(char** argv)
{
	g_tarServerConfig.m_strCmdName = argv[0];
	g_tarServerConfig.m_strIP = argv[1];
	g_tarServerConfig.m_strPort = argv[2];
	g_tarServerConfig.m_strDownloadPath = argv[3];
 	g_tarServerConfig.m_strUploadPath = argv[4];

	if (g_tarServerConfig.m_strUploadPath.at(g_tarServerConfig.m_strUploadPath.length() - 1) == '\\')
	{
		g_tarServerConfig.m_strUploadPath = g_tarServerConfig.m_strUploadPath.substr(0, g_tarServerConfig.m_strUploadPath.length() - 1);
	}

	if (g_tarServerConfig.m_strDownloadPath.at(g_tarServerConfig.m_strDownloadPath.length() - 1) == '\\')
	{
		g_tarServerConfig.m_strDownloadPath = g_tarServerConfig.m_strDownloadPath.substr(0, g_tarServerConfig.m_strDownloadPath.length() - 1);
	}
}