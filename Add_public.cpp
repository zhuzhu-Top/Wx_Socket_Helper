
#include "PubLic.h"
#include "pch.h"
#include <iostream>

#include "HWeChat.h"

#include "pch.h"


#include "jsonxx/json.hpp"

DWORD getWeChatwinADD();
void Add_Public(std::wstring wx_id) {

    DWORD call_1 = getWeChatwinADD() + 0x1D69F0;
    WxString wxid;



    //std::wstring dddd = L"gh_650586eed01c";
    wxid.pstr = (wchar_t*)wx_id.c_str();
    wxid.len = wx_id.size();
    wxid.maxLen = wx_id.size() * 2;

    HWND Hwnd = FindWindow(L"WeChatMainWndForPC", 0);
    DWORD dwCore = GetWindowLong(Hwnd, GWLP_USERDATA);
    dwCore += 0x610;

    char buff[0x500] = { 0 };

    __asm {

        pushad

        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x0
        push 0x11
        push 0x1

        mov edi, dwCore

        lea ecx, ds: [edi - 0x5E0]
        mov eax, dword ptr ds : [ecx]
        push eax




        mov ecx, -1
        lea eax, ds: [edi + 0x2DC]
        and ecx, eax
        push ecx

        lea esi, wxid


        push esi
        lea ecx, ds : [edi + 0xD80]


        call call_1

        popad
    }

}