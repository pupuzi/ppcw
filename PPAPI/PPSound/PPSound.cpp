#include "PPSound.h"
#include <corecrt_math.h>

CPPSound::CPPSound()
{
	pDs = nullptr;
	pDSB = nullptr;

	GUID oGuid;
	GetDeviceID(&DSDEVID_DefaultPlayback, &oGuid);
	DirectSoundCreate(&oGuid, &pDs, NULL);
	pDs->SetCooperativeLevel(GetConsoleWindow(), DSSCL_NORMAL);
}

CPPSound::~CPPSound()
{
	pDs->Release();
	pDSB->Release();
}

LPDIRECTSOUNDBUFFER CPPSound::Load(const wchar_t* strFilePath)
{
	HMMIO hMmio;
	MMRESULT mmResult;
	hMmio = mmioOpen(const_cast<wchar_t*>(strFilePath), NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (!hMmio)
		return NULL;

	MMCKINFO mmCkRiff;//WAVE文件信息结构
	mmCkRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmResult = mmioDescend(hMmio, &mmCkRiff, NULL, MMIO_FINDRIFF);
	if (mmResult != MMSYSERR_NOERROR)
		return NULL;

	MMCKINFO mmCkInfo;
	mmCkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');//设定区块类型
	mmResult = mmioDescend(hMmio, &mmCkInfo, &mmCkRiff, MMIO_FINDCHUNK);//此方法退出区块
	if (mmResult != MMSYSERR_NOERROR)
		return NULL;

	//读取音频格式
	WAVEFORMATEX oFormat;
	if (mmioRead(hMmio, (HPSTR)&oFormat, sizeof(oFormat)) == -1)
		return NULL;

	mmioAscend(hMmio, &mmCkInfo, 0);
	mmCkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = mmioDescend(hMmio, &mmCkInfo, &mmCkRiff, MMIO_FINDCHUNK);
	if (mmResult != MMSYSERR_NOERROR)
		return NULL;

	//创建音频次缓冲区
	LPDIRECTSOUNDBUFFER pTempBuf;
	DSBUFFERDESC desc;//用以描述缓冲区结构
	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.lpwfxFormat = &oFormat;
	desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME;//static表示可多次播放，当然还可以指定其他的使用| 连接
	desc.dwBufferBytes = mmCkInfo.cksize;
	HRESULT hRes = pDs->CreateSoundBuffer(&desc, &pTempBuf, NULL);
	if (hRes != DS_OK)
		return NULL;

	// 从文件读取音频数据存入次缓冲区
	LPVOID pAudio;
	DWORD BytesAudio;
	pTempBuf->Lock(0, mmCkInfo.cksize, &pAudio, &BytesAudio, NULL, NULL, NULL);
	if (mmioRead(hMmio, (HPSTR)pAudio, BytesAudio) == -1)
		return NULL;
	pTempBuf->Unlock(pAudio, BytesAudio, NULL, NULL);

	//关闭文件
	mmioClose(hMmio, 0);

	return pTempBuf;
}

BOOL CPPSound::LoadSound(CPPString& strFilePath)
{
	pDSB = Load(strFilePath.GetString());
	if (!pDSB)
		return FALSE;
	return TRUE;
}

BOOL CPPSound::LoadSound(const wchar_t* strFilePath)
{
	pDSB = Load(strFilePath);
	if (!pDSB)
		return FALSE;
	return TRUE;
}

BOOL CPPSound::SetVolume(float uNum)
{
	if (uNum > 100)
		return FALSE;
	if (uNum == 0)
	{
		pDSB->SetVolume(-10000);
		return TRUE;
	}
	else if (pDSB->SetVolume(2000.0 * log10(uNum / 100)) != S_OK)
			return FALSE;
	return TRUE;
}

BOOL CPPSound::PlaySond()
{
	if (pDSB->Play(0, 0, 1) != S_OK)
		return FALSE;
	return TRUE;
}

