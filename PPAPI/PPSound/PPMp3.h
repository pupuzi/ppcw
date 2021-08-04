#pragma once

typedef struct __CPPMP3HEADER //MP3ͷ�ṹ
{
	char strID3[3]; //ID3
	char chVersion; //ID3�汾
	char chRevision;  //���汾
	char chFlag; //��־
	unsigned char strSize[4]; //��ǩ��С
} CPPMP3HEADER;

typedef struct __CPPMP3TAG //MP3��ǩ
{
	char strTagID[4];
	unsigned char strSize[4]; 
	char strFlags[2];
}CPPMP3TAG;

typedef struct __CPPSOUNDINFO //MP3����
{
	char strTitle[256];
	int nTitleSize;
	char strName[256];
	int nNameSize;
	char strAlbum[256];
	int nAlbumSize;

	void SetTitle(FILE* pFile, int nLen)
	{
		//3��ָ 01 FF FE
		fseek(pFile, 3, SEEK_CUR);
		fread(strTitle, 1, nLen - 3, pFile);
		nTitleSize = nLen - 3;

		for (int i = 0; i < nTitleSize; i++)
		{
			for (int n = 0; n < nTitleSize - 1; n++)
			{
				if (strTitle[n] == '\0')
				{
					char chTemp = strTitle[n];
					strTitle[n] = strTitle[n + 1];
					strTitle[n + 1] = chTemp;
				}
			}
		}

		nTitleSize = strlen(strTitle);
	}

	void SetName(FILE* pFile, int nLen)
	{
		//3��ָ 01 FF FE
		fseek(pFile, 3, SEEK_CUR);
		fread(strName, 1, nLen - 3, pFile);
		nNameSize = nLen - 3;

		for (int i = 0; i < nNameSize; i++)
		{
			for (int n = 0; n < nNameSize - 1; n++)
			{
				if (strName[n] == '\0')
				{
					char chTemp = strName[n];
					strName[n] = strName[n + 1];
					strName[n + 1] = chTemp;
				}
			}
		}

		nNameSize = strlen(strName);
	}

	void SetAlbum(FILE* pFile, int nLen)
	{
		//3��ָ 01 FF FE
		fseek(pFile, 3, SEEK_CUR);
		fread(strAlbum, 1, nLen - 3, pFile);
		nAlbumSize = nLen - 3;

		for (int i = 0; i < nAlbumSize; i++)
		{
			for (int n = 0; n < nAlbumSize - 1; n++)
			{
				if (strAlbum[n] == '\0')
				{
					char chTemp = strAlbum[n];
					strAlbum[n] = strAlbum[n + 1];
					strAlbum[n + 1] = chTemp;
				}
			}
		}

		nAlbumSize = strlen(strAlbum);
	}

}CPPSOUNDINFO;

void CPPMP3_Parse(FILE* pFile, CPPSOUNDINFO* pInfo)
{
	//ȷ����MP3 ID3v2.3�汾
	char strTempMemory[10] = { 0 };
	CPPMP3HEADER oID3Header;
	size_t size = sizeof(oID3Header);
	fread(strTempMemory, 1, size, pFile);
	memcpy(&oID3Header, strTempMemory, size);
	if (oID3Header.strID3[0] != 'I' 
		|| oID3Header.strID3[1] != 'D'
		|| oID3Header.strID3[2] != '3')
		return;
	//ȡ��Ϣtag
	CPPMP3TAG oID3Tag;
	size = sizeof(oID3Tag);
	while (oID3Tag.strTagID[0] != '\0'
		|| oID3Tag.strTagID[1] != '\0'
		|| oID3Tag.strTagID[2] != '\0'
		|| oID3Tag.strTagID[3] != '\0')
	{
		fread(strTempMemory, 1, size, pFile);
		memcpy(&oID3Tag, strTempMemory, size);
		int nLen = oID3Tag.strSize[0] * 0x1000000 + oID3Tag.strSize[1] * 0x10000 + oID3Tag.strSize[2] * 0x100 + oID3Tag.strSize[3];
		if (oID3Tag.strTagID[0] == 'T' && oID3Tag.strTagID[1] == 'I' && oID3Tag.strTagID[2] == 'T' && oID3Tag.strTagID[3] == '2')
		{
			pInfo->SetTitle(pFile, nLen);
		}
		else if (oID3Tag.strTagID[0] == 'T' && oID3Tag.strTagID[1] == 'P' && oID3Tag.strTagID[2] == 'E' && oID3Tag.strTagID[3] == '1')
		{
			pInfo->SetName(pFile, nLen);
		}
		else if (oID3Tag.strTagID[0] == 'T' && oID3Tag.strTagID[1] == 'A' && oID3Tag.strTagID[2] == 'L' && oID3Tag.strTagID[3] == 'B')
		{
			pInfo->SetAlbum(pFile, nLen);
		}
		else
			fseek(pFile, nLen, SEEK_CUR);
	}
}