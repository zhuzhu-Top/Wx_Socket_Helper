// MemOpt.h: interface for the CMemOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMOPT_H__659AA101_2C5E_409B_B656_49DEF306159D__INCLUDED_)
#define AFX_MEMOPT_H__659AA101_2C5E_409B_B656_49DEF306159D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemOpt  
{
	public:
		CMemOpt(HANDLE hProcess,DWORD dwBase,int vOffset[]=NULL,int nCount=0);
		virtual ~CMemOpt();
		bool ReadMem(void *pBuf,int nCount);
		bool WriteMem(void *pBuf,int nCount);
		bool ReadOffsetMem(int vOffset[],int nSize,void *pBuf,int nCount);
	private:
		HANDLE  m_hProcess;
		void   *m_pBase;

};

#endif // !defined(AFX_MEMOPT_H__659AA101_2C5E_409B_B656_49DEF306159D__INCLUDED_)
