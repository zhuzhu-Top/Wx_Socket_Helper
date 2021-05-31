#include "PubLic.h"
#include "pch.h"
#include <iostream>

#include "HWeChat.h"

#include "pch.h"


#include "jsonxx/json.hpp"
DWORD getWeChatwinADD();


void CllectMoney(wchar_t* transferid, wchar_t* wxid)
{
    struct CllectMoneyStruct
    {
        wchar_t* ptransferid;
        int transferidLen;
        int transferidMaxLen;
        char full[0x8] = { 0 };
        wchar_t* pwxid;
        int wxidLen;
        int wxidMaxLen;
        char full2[0x8] = { 0 };
    };

    CllectMoneyStruct cllect;
    cllect.ptransferid = transferid;
    cllect.transferidLen = wcslen(transferid) + 1;
    cllect.transferidMaxLen = (wcslen(transferid) + 1) * 2;
    cllect.pwxid = wxid;
    cllect.wxidLen = wcslen(wxid) + 1;
    cllect.wxidMaxLen = (wcslen(wxid) + 1) * 2;

    char* asmBuff = (char*)&cllect.ptransferid;

    //9B3F40
    //    9B3FC0

    DWORD dwCall1 = getWeChatwinADD() + 0x9B3F40;
    DWORD dwCall2 = getWeChatwinADD() + 0x9B3FC0;


    __asm
    {
        sub esp, 0x30;
        mov ecx, esp;
        mov eax, asmBuff;
        push eax;
        call dwCall1;
        call dwCall2;
        add esp, 0x30;
    }
}