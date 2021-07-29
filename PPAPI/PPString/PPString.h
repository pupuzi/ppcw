#pragma once
#include "../PPDef.h"
#include <tchar.h>

class CPPString
{
private:
	wchar_t* m_wstrValue;
	uint m_uLength;

public:
	//构造与析构
	CPPString();
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
	void __CopyMemory(const wchar_t* pMemory, uint uLen);
	void __CopyMemoryOfs(const wchar_t* pMemory, uint uOffset, uint uLen);

public:
	//自用函数
	wchar_t* __GetWStrValue();

public:
	//通用函数
	uint GetLength();
	wchar_t GetAt(uint uIndex);
	const wchar_t* GetString();
};