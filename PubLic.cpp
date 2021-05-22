#include "PubLic.h"

#include "pch.h"



DWORD getWeChatwinADD() {
    //微信模块基质
    HMODULE WinAdd = LoadLibrary(L"WeChatWin.dll");
    //printf("%d", WinAdd);
    return (DWORD)WinAdd;
}

DWORD Read_OriFun_ADD(HANDLE hProcess, DWORD AddTo_Read) {
	DWORD jmp_BAck_Add = AddTo_Read + 0x5;
	DWORD dwTemp = 0;
	char read_data[5] = { 0 };
	unsigned long  Hard_code = 0;
	::ReadProcessMemory(hProcess, (LPCVOID)AddTo_Read, read_data, 5, &dwTemp);
	::memcpy_s(&Hard_code, 4, &read_data[1], 4);
	//DWORD original_Fun_head = jmp_BAck_Add + hard_code;
	return jmp_BAck_Add + Hard_code;
}