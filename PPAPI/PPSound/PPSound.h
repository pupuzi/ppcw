#pragma once
#include "PPSoundDef.h"

#include "../PPString/PPString.h"
#include "../PPObj/PPObj.h"

class CPPSound
{
private:
	CPPString m_strName;
	CPPString m_strAuthor;
	CPPString m_strFilePath;
	unsigned int m_uTotalTime;
	unsigned int m_uCurrentTime;

	IGraphBuilder* m_pGraphBuilder;
	IMediaControl* m_pMediaControl;
	IMediaPosition* m_pMediaPosition ;

public:
	CPPSound();
	virtual ~CPPSound();

private:
	BOOL Load(const wchar_t* strFilePath);
	void ParseExtension(const wchar_t* strFilePath);

public:
	BOOL Init();
	void Exit();
	BOOL LoadSound(CPPString& strFilePath);
	BOOL LoadSound(const wchar_t* strFilePath);
	BOOL PlaySound();
	BOOL StopSound();
	BOOL PauseSound();
};