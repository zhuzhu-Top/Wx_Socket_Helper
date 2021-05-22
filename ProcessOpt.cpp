#include "pch.h"
#include "ProcessOpt.h"

CProcessOpt::CProcessOpt(DWORD dwProcessID,DWORD dwAccess)
{
	m_hProcess=OpenProcess(dwAccess,FALSE,dwProcessID);
}

CProcessOpt::~CProcessOpt(void)
{
	CloseHandle(m_hProcess);
}
