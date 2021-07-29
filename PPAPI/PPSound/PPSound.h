#pragma once
#include "PPSoundDef.h"

#include "../PPString/PPString.h"
#include "../PPObj/PPObj.h"

class CPPSound : public CPPObj
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
	virtual ~CPPSound() {}

public:
	LPDIRECTSOUNDBUFFER  LoadSound(const wchar_t* strFilePath);

	BOOL PlaySond(const wchar_t* strFilePath);
	BOOL PlaySond(CPPString& strFilePath);
};