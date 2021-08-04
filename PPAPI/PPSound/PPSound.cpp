#include "PPSound.h"
#include "PPMp3.h"
#include <corecrt_math.h>

CPPSound::CPPSound()
{
	m_uTotalTime = 0;
	m_uCurrentTime = 0;

	m_pGraphBuilder = NULL;
	m_pMediaControl = NULL;
	m_pMediaPosition = NULL;
}

CPPSound::~CPPSound()
{
	m_pGraphBuilder->Release();
	m_pMediaPosition->Release();
	m_pMediaControl->Release();
}

BOOL CPPSound::Init()
{
	if (CoInitialize(NULL) != S_OK)
		return FALSE;
	return TRUE;
}

void CPPSound::Exit()
{
	CoUninitialize();
}

BOOL CPPSound::Load(const wchar_t* strFilePath)
{
	FILE* fp;
	CPPSOUNDINFO oInfo;
	_wfopen_s(&fp, strFilePath, _T("rb"));
	CPPMP3_Parse(fp, &oInfo);
	fclose(fp);

	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);
	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);
	m_pGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pMediaPosition);
	if (m_pGraphBuilder->RenderFile(strFilePath, NULL) != S_OK)
		return FALSE;
	return TRUE;
}

void CPPSound::ParseExtension(const wchar_t* strFilePath)
{

}

BOOL CPPSound::LoadSound(CPPString& strFilePath)
{
	return Load(strFilePath.GetString());
}

BOOL CPPSound::LoadSound(const wchar_t* strFilePath)
{
	return Load(strFilePath);
}

BOOL CPPSound::PlaySound()
{
	if (m_pMediaControl->Run() != S_OK)
		return FALSE;
	return TRUE;
}

BOOL CPPSound::StopSound()
{
	if (m_pMediaControl->Stop() != S_OK)
		return FALSE;
	return TRUE;
}

BOOL CPPSound::PauseSound()
{
	if (m_pMediaControl->Pause() != S_OK)
		return FALSE;
	return TRUE;
}


