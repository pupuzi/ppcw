#pragma once
#include <tchar.h>
#include "../PPDef.h"

class CPPString
{
private:
	wchar_t* m_wstrValue;
	unsigned int m_uLength;

public:
	//����������
	CPPString();
	CPPString(const wchar_t* wstrValue);
	CPPString(CPPString& wstrValue);
	virtual ~CPPString();

	CPPString& operator=(const wchar_t* wstrValue);
	CPPString& operator=(CPPString& wstrValue);
	CPPString& operator=(wchar_t wstrValue);
	BOOL operator==(CPPString& wstrValue);
	BOOL operator!=(CPPString& wstrValue);
	CPPString& operator+=(CPPString& wstrValue);
	CPPString& operator+=(const wchar_t* wstrValue);

private:
	BOOL __Compare(CPPString& wstr1, CPPString& wstr2);
	void __CopyMemory(const wchar_t* pMemory, unsigned int uLen);
	void __CopyMemoryOfs(const wchar_t* pMemory, unsigned int uOffset, unsigned int uLen);

public:
	//���ú���
	wchar_t* __GetWStrValue();

public:
	//ͨ�ú���
	unsigned int GetLength();
	wchar_t GetAt(unsigned int uIndex);
	const wchar_t* GetString();
};