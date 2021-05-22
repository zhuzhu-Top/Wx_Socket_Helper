// MemOpt.cpp: implementation of the CMemOpt class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#include <Windows.h>
#include "MemOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemOpt::CMemOpt(HANDLE hProcess,DWORD dwBase,int vOffset[],int nCount)
{
	m_hProcess=hProcess;
	m_pBase=(void*)dwBase;
	if (nCount > 0)
	{
		DWORD dwAddr=0;
		ReadOffsetMem(vOffset,nCount-1,&dwAddr,4);
		m_pBase=(void*)(dwAddr+vOffset[nCount-1]);
	}
}

CMemOpt::~CMemOpt()
{

}

bool CMemOpt::ReadMem(void *pBuf,int nCount)
{
	DWORD dwTemp=0;
	return ::ReadProcessMemory(m_hProcess,m_pBase,pBuf,nCount,&dwTemp);
}

bool CMemOpt::WriteMem(void *pBuf,int nCount)
{
	DWORD dwTemp=0;
	return ::WriteProcessMemory(m_hProcess,m_pBase,pBuf,nCount,&dwTemp);
}

bool CMemOpt::ReadOffsetMem(int vOffset[],int nSize,void *pBuf,int nCount)
{
	DWORD dwTemp=0;
	void *pBaseAddr=m_pBase;
	DWORD dwAddr=0;
	for (int i=0;i<nSize;i++)
	{
		if (!::ReadProcessMemory(m_hProcess,pBaseAddr,&dwAddr,4,&dwTemp))
			return false;
		pBaseAddr=(void*)(dwAddr+vOffset[i]);
	}
	return ::ReadProcessMemory(m_hProcess,pBaseAddr,pBuf,nCount,&dwTemp);
}
