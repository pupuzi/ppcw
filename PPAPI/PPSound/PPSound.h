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

	LPDIRECTSOUND pDs;
	LPDIRECTSOUNDBUFFER pDSB;

public:
	CPPSound();
	virtual ~CPPSound();

private:
	LPDIRECTSOUNDBUFFER Load(const wchar_t* strFilePath);

public:
	BOOL LoadSound(CPPString& strFilePath);
	BOOL LoadSound(const wchar_t* strFilePath);
	BOOL SetVolume(float uNum);
	BOOL PlaySond();
};