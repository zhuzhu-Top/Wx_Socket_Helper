#include "PubLic.h"
#include "pch.h"
#include <iostream>

#include "HWeChat.h"

#include "pch.h"


#include "jsonxx/json.hpp"
DWORD getWeChatwinADD();

void Verify_Add_Frind(std::wstring wxid, std::wstring msg) {

    /*
    * ebx
    $ ==> > 1313A630  UNICODE "wxid_4zr616ir6fi122"
    $ + 4 > 00000013
    $ + 8 > 00000013
    $ + C > 00000000
    $ + 10 > 00000000
    $ + 14 > 12BB1170  UNICODE "ˉ"
    $ + 18 > 12BB1180
    $ + 1C > 12BB1180
    $ + 20 > 1C10D728
    $ + 24 > 1318A3F8  UNICODE "我是加好友啊"

    */
    DWORD dwParam1 = getWeChatwinADD() + (0x7C11BB18 - 0x7AA10000);
    DWORD dwCall1 = getWeChatwinADD() + (0x7AA67590 - 0x7AA10000);
    DWORD dwCall2 = getWeChatwinADD() + (0x7AA93500 - 0x7AA10000);
    DWORD dwCall3 = getWeChatwinADD() + (0x7AF9C4A0 - 0x7AA10000);
    DWORD dwCall4 = getWeChatwinADD() + (0x7AF9C4E0 - 0x7AA10000);
    DWORD dwCall5 = getWeChatwinADD() + (0x7AD31AA0 - 0x7AA10000);
    DWORD dwCall6 = getWeChatwinADD() + (0x7AA73660 - 0x7AA10000);

    struct TextStruct
    {
            wchar_t* pStr;
            int strLen;
        int strMaxLen;

    };

    TextStruct pWxid = { 0 };
    pWxid.pStr = (wchar_t*)wxid.c_str();
    pWxid.strLen = (wxid).size() + 1;
    pWxid.strMaxLen = ((wxid).size() + 1) * 2;


    TextStruct pMsg = { 0 };
    pMsg.pStr = (wchar_t*)msg.c_str();
    pMsg.strLen = (msg).size() + 1;
    pMsg.strMaxLen = ((msg).size() + 1) * 2;

    char* asmWxid = (char*)&pWxid.pStr;
    char* asmMsg = (char*)&pMsg.pStr;
    DWORD asmMsgText = (DWORD)pMsg.pStr;
    char buff3[0x100] = { 0 };
    char* buff = buff3;
    __asm
    {
        sub esp, 0x18;
        mov ecx, esp;
        mov dword ptr ss : [ebp - 0xDC] , esp;
        push  dwParam1;
        call dwCall1;


        sub esp, 0x18;
        mov eax, buff;
        mov dword ptr ss : [ebp - 0xE4] , esp;
        mov ecx, esp;
        push eax;
        call dwCall2;


        push 0x6;            //好友验证
        sub esp, 0x14;
        mov ecx, esp;
        mov dword ptr ss : [ebp - 0xE8] , esp;
        push - 0x1;
        mov edi, asmMsgText;
        push edi;
        call dwCall3;


        mov eax, asmMsg;
        push 0x2;
        sub esp, 0x14;
        mov ecx, esp;
        mov dword ptr ss : [ebp - 0xE0] , esp;
        mov ebx, asmWxid;
        push ebx;
        call dwCall4;

        call dwCall6;


        mov ecx, eax;
        call dwCall5;
    }

}