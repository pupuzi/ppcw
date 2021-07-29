#pragma once

class CPPObj
{
private:
	CPPObj* m_pNext;
	CPPObj* m_pPrev;
	CPPObj* m_pParent;
	CPPObj* m_pChild;

public:
	CPPObj() {}
	virtual ~CPPObj() {}

	CPPObj* GetNext() { return m_pNext; }
	CPPObj* GetPrev() { return m_pPrev; }
	CPPObj* GetParent() { return m_pParent; }
	CPPObj* GetChild() { return m_pChild; }
	CPPObj* SetNext(CPPObj* pNext) { m_pNext = pNext; }
	CPPObj* SetPrev(CPPObj* pPrev) { m_pPrev = pPrev; }
	CPPObj* SetParent(CPPObj* pParent) { m_pParent = pParent; }
	CPPObj* SetChild(CPPObj* pChild) { m_pChild = pChild; }

public:

};