#include "PubLic.h"
#include "pch.h"
#include <iostream>

#include "HWeChat.h"

#include "pch.h"


#include "jsonxx/json.hpp"


void AgreeUserRequest(wchar_t* v1, wchar_t* v2)
{
    struct v1Info
    {
        int fill = 0;
        wchar_t* v1 = 0;
        int v1Len;
        int maxV1Len;
        char fill2[0x41C] = { 0 };
        DWORD v2 = { 0 };
    };

    struct v2Info
    {
        char fill[0x24C] = { 0 };
        DWORD fill3 = 0x25;
        char fill4[0x40] = { 0 };
        wchar_t* v2;
        int v2Len;
        int maxV2Len;
        char fill2[0x8] = { 0 };
    };

    DWORD callAdd1 = getWeChatwinADD() + (0x621BFE60 - 0x61FD0000);
    DWORD callAdd2 = getWeChatwinADD() + (0x6202D590 - 0x61FD0000);
    DWORD callAdd3 = getWeChatwinADD() + (0x620DFD10 - 0x61FD0000);
    DWORD callAdd4 = getWeChatwinADD() + (0x621A6C80 - 0x61FD0000);
    DWORD params = getWeChatwinADD() + (0x63A57138 - 0x61FD0000);//0x63A57138

    DWORD* asmP = (DWORD*)params;

    v1Info userInfoV1 = { 0 };
    v2Info userInfoV2 = { 0 };
    userInfoV1.v2 = (DWORD)&userInfoV2.fill;
    userInfoV1.v1 = v1;
    userInfoV1.v1Len = wcslen(v1);
    userInfoV1.maxV1Len = wcslen(v1) * 2;

    userInfoV2.v2 = v2;
    userInfoV2.v2Len = wcslen(v2);
    userInfoV2.maxV2Len = wcslen(v2) * 2;

    char* asmUser = (char*)&userInfoV1.fill;
    char buff[0x14] = { 0 };
    char buff2[0x48] = { 0 };
    char* asmBuff = buff2;


    char buff_ecx[0x300] = { 0 };
    char buff_edx[0x300] = { 0 };
    __asm
    {
        pushad

        mov ecx, asmUser;
        push 0xE;
        sub esp, 0x14;
        push esp;
        call callAdd1;
        mov ecx, asmUser;
        lea eax, buff;
        push eax;
        call callAdd2;
        mov esi, eax;
        sub esp, 0x8;
        mov ecx, asmP;
        call callAdd3;
        lea ecx, buff_ecx;
        lea edx, buff_edx;
        push eax;
        push edx;
        push esi;
        call callAdd4;

        popad
    }

}
