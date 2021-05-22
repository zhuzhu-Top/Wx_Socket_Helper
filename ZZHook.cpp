#include "pch.h"
#include "ZZHook.h"
#pragma warning(disable:4996)
std::wstring String2WString(const std::string& s)
{
	const char* chSrc = s.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	std::wstring wstrResult = wchDest;
	delete[]wchDest;
	return wstrResult;
}
std::string WString2String(const std::wstring& ws)
{
	const wchar_t* wchSrc = ws.c_str();
	size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
	char* chDest = new char[nDestSize];
	memset(chDest, 0, nDestSize);
	wcstombs(chDest, wchSrc, nDestSize);
	std::string strResult = chDest;
	delete[]chDest;
	return strResult;
}

Hook::Hook(DWORD hookAddr) {
	ZeroMemory(this->backCode, 5);
	this->hookAddr = hookAddr;
	this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());
	//this->hProcess =GetCurrentProcess();
	if (this->hProcess== NULL)
	{
		Log("Hook 打开进程失败");
		return;
	}
	if (ReadProcessMemory(hProcess, (LPVOID)hookAddr, this->backCode, 5, NULL) == 0) {
		Log("ReadProcessMemory error");
		Log("GetLastError  -->"<<GetLastError())
	
	}
};
int Hook::StartHook(LPVOID Naked_fun_space, DWORD My_fun) {//Naked_fun_space 自己的裸函数被写入的地址
	DWORD jmpAddr = (DWORD)Naked_fun_space - (this->hookAddr + 5);
	BYTE jmpCode[5] = {0};
	*(jmpCode + 0) = 0xE9;
	*(DWORD*)(jmpCode + 1) = jmpAddr;

	//DWORD tmmmmmp = (DWORD)My_fun;
	char* My_fun_add = nullptr;
	//DWORD_To_char(tmmmmmp, p);
	DWORD_To_char(My_fun, My_fun_add);

	DWORD jmp_BAck_Add = this->hookAddr + 0x5;
	char* Back_add = nullptr;
	DWORD_To_char(jmp_BAck_Add, Back_add);


	unsigned long  hard_code = 0;


	if (memcpy_s(&hard_code, 4, &this->backCode[1], 4))
	{
		printf_s("copy to hard_code fialure\n");
		return -1;
	}



	DWORD original_Fun_head = jmp_BAck_Add + hard_code;
	printf_s("this->backCode  -- %X \n", this->backCode);
	printf_s("jmp_BAck_Add %X   +  hard_code  +  %X   original_Fun_head   -->  %X", jmp_BAck_Add, hard_code,original_Fun_head);
	Shell_Code uu(My_fun_add, Back_add, original_Fun_head);

	memcpy(Naked_fun_space, &uu, sizeof(uu));

	if (WriteProcessMemory(this->hProcess, (LPVOID)hookAddr, jmpCode, 5, NULL) == 0) {
		return -1;
	}

	return 0;

};
bool Hook::UnHook() {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());
	if (WriteProcessMemory(hProcess, (LPVOID)(this->hookAddr), this->backCode, 5, NULL) == 0) {
		return 1;
	}
	return 0;
}

void DWORD_To_char(DWORD& address, char*& arry) {
	arry = (char*)&address;
}