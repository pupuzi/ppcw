#include "PPString.h"

CPPString::CPPString()
{
	m_uLength = 0;
	m_wstrValue = new wchar_t[1];
	m_wstrValue[0] = '\0';
}

CPPString::~CPPString()
{
	delete[] m_wstrValue;
}

CPPString& CPPString::operator=(const wchar_t* wstrValue)
{
	unsigned int uLen = wcslen(wstrValue);
	__CopyMemory(wstrValue, uLen);
	return *this;
}

CPPString& CPPString::operator=(CPPString& wstrValue)
{
	unsigned int uLen = wstrValue.GetLength();
	__CopyMemory(wstrValue.__GetWStrValue(), uLen);
	return *this;
}

CPPString& CPPString::operator=(wchar_t wstrValue)
{
	unsigned int uLen = 1;
	__CopyMemory(&wstrValue, uLen);
	return *this;
}

BOOL CPPString::operator==(CPPString& wstrValue)
{
	if (m_uLength != wstrValue.GetLength())
		return FALSE;
	return __Compare(*this, wstrValue);
}

BOOL CPPString::operator!=(CPPString& wstrValue)
{
	if (m_uLength == wstrValue.GetLength())
		return FALSE;
	return !__Compare(*this, wstrValue);
}

CPPString& CPPString::operator+=(CPPString& wstrValue)
{
	wchar_t* wstrTemp = new wchar_t[m_uLength + 1];
	wmemcpy(wstrTemp, m_wstrValue, m_uLength);
	wstrTemp[m_uLength] = '\0';
	unsigned int uLen = m_uLength;
	__CopyMemory(wstrTemp, wstrValue.GetLength() + m_uLength);
	__CopyMemoryOfs(wstrValue.__GetWStrValue(), uLen, wstrValue.GetLength());
	delete [] wstrTemp;
	return *this;
}

CPPString& CPPString::operator+=(const wchar_t* wstrValue)
{
	wchar_t* wstrTemp = new wchar_t[m_uLength + 1];
	wmemcpy(wstrTemp, m_wstrValue, m_uLength);
	wstrTemp[m_uLength] = '\0';
	unsigned int uLen = m_uLength;
	__CopyMemory(wstrTemp, wcslen(wstrValue) + m_uLength);
	__CopyMemoryOfs(wstrValue, uLen, wcslen(wstrValue));
	delete[] wstrTemp;
	return *this;
}

BOOL CPPString::__Compare(CPPString& wstr1, CPPString& wstr2)
{
	//仅负责比对相同长度的字符串
	for (unsigned int i = 0; i < wstr1.GetLength(); i++)
	{
		if (wstr1.GetAt(i) != wstr2.GetAt(i))
			return FALSE;
	}
	return TRUE;
}

void CPPString::__CopyMemory(const wchar_t* pMemory, unsigned int uLen)
{
	delete[] m_wstrValue;
	m_wstrValue = new wchar_t[uLen + 1];
	wmemcpy(m_wstrValue, pMemory, uLen);
	m_wstrValue[uLen] = '\0';
	m_uLength = uLen;
}

void CPPString::__CopyMemoryOfs(const wchar_t* pMemory, unsigned int uOffset, unsigned int uLen)
{
	wmemcpy(&m_wstrValue[uOffset], pMemory, uLen);
	m_wstrValue[m_uLength] = '\0';
}

wchar_t* CPPString::__GetWStrValue()
{
	return m_wstrValue;
}

size_t CPPString::GetLength()
{
	return m_uLength;
}

wchar_t CPPString::GetAt(unsigned int uIndex)
{
	ASSERT(uIndex < m_uLength);
	return m_wstrValue[uIndex];
}

const wchar_t* CPPString::GetString()
{
	return m_wstrValue;
}