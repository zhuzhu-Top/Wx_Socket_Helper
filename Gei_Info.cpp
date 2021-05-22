//#include <Windows.h>
//#include <string.h>
//#include <iostream>

#include "PubLic.h"
#include "pch.h"
#include <iostream>

#include "HWeChat.h"

#include "pch.h"


#include "jsonxx/json.hpp"
#include "cvtcode.hpp"


jsonxx::json Friend_List;

DWORD getWeChatwinADD();

BOOL GetUserInfoByWxid(std::wstring wxid, WxUserInfo* info) {

    //7A880000

    //    7AAFB845    8DBE 280F0000   lea edi, dword ptr ds : [esi + 0xF28]
    //    7AAFB84B    57              push edi; 微信信息结构体
    //    7AAFB84C    83EC 14         sub esp, 0x14
    //    7AAFB84F    8D45 08         lea eax, dword ptr ss : [ebp + 0x8]
    //    7AAFB852    8BCC            mov ecx, esp
    //                                                                   7AAFB854    8965 D4         mov dword ptr ss : [ebp - 0x2C] , esp
    //    7AAFB857    50              push eax;                  wxid
    //    7AAFB858    E8 830C3100     call WeChatWi.7AE0C4E0; wxid获取好友信息
    //    7AAFB85D    90              nop
    //    7AAFB85E    90              nop
    //    7AAFB85F    90              nop
    //    7AAFB860    90              nop
    //    7AAFB861    E8 FA7DDEFF     call WeChatWi.7A8E3660
    //    7AAFB866    0000            add byte ptr ds : [eax] , al
    //    7AAFB868    0000            add byte ptr ds : [eax] , al
    //    7AAFB86A    E8 F17C0A00     call WeChatWi.7ABA3560

    WxString tmp = { 0 };
    tmp.pstr = (wchar_t*)wxid.c_str();
    tmp.len = wxid.size();
    tmp.maxLen = wxid.size() * 2;

    DWORD call_1 = getWeChatwinADD() + (0x7AE0C4E0 - 0x7A880000);
    DWORD call_2 = getWeChatwinADD() + (0x7A8E3660 - 0x7A880000);
    DWORD call_3 = getWeChatwinADD() + (0x7ABA3560 - 0x7A880000);

    int ret = 0;
    __asm {
        pushad
        pushfd

        mov edi, info
        push edi
        sub esp, 0x14
        lea eax, tmp
        mov ecx, esp
        push eax

        call call_1
        call call_2
        call call_3

        mov ret, eax

        popfd
        popad
    }
    return ret == 1;

}



VOID Ergodic(const char* prefix, DWORD start, DWORD end) {
    std::wstring wxid = HTools::ReadUnicodeString(start + 0x30);
    std::wstring name = HTools::ReadUnicodeString(start + 0x8c);
    std::cout << "   " << prefix << "    " << std::hex << start;
    std::cout << "   " << HTools::w2s(wxid).c_str();
    std::cout << "   " << HTools::w2s(name).c_str() << std::endl;;

    Friend_List[uc2u8(name)] = uc2u8(wxid);
    DWORD left = HTools::ReadInt(start);
    if (left != end)
    {
        Ergodic("Left", left, end);
    }
    DWORD right = HTools::ReadInt(start + 0x8);
    if (right != end)
    {
        Ergodic("right", right, end);
    }
}



std::string Get_Group_Mem_Wxid(std::wstring RoomWxid) {
    WxString wxid = { 0 };
    wxid.pstr = (wchar_t*)RoomWxid.c_str();
    wxid.len = RoomWxid.size();
    wxid.maxLen = RoomWxid.size() * 2;

    struct TMP
    {
        char Zero[4] = { 0 };
        char wxid[4] = { 0 };
        char wxid_Len[4] = { 0 };
        char wxid_Max_Len[4] = { 0 };
        char Zero_1[0x8] = { 0 };
        char** group_wxid[0x4] = { 0 };   //记录群里所有人的指针
        char Zero_3[0x500] = { 0 };

    };

    TMP buff;

    DWORD call_1 = getWeChatwinADD() + 0x511A60;//37 86B0
    DWORD call_2 = getWeChatwinADD() + (0x796D86B0 - 0x79360000);//37 86B0
    DWORD call_3 = getWeChatwinADD() + (0x79878080 - 0x79360000);//518080
    //MessageBoxA(NULL, "ok", "ok", MB_OK);
    //79360000              303C29
    //    79663C29    8D8D 98FEFFFF   lea ecx, dword ptr ss : [ebp - 0x168]
    //    79663C2F    E8 2CDE2000     call WeChatWi.79871A60
    //    79663C34    8D85 98FEFFFF   lea eax, dword ptr ss : [ebp - 0x168]
    //    79663C3A    C745 FC 0100000 > mov dword ptr ss : [ebp - 0x4] , 0x1
    //    79663C41    50              push eax
    //    79663C42    56              push esi
    //    79663C43    E8 684A0700     call WeChatWi.796D86B0
    //    79663C48    8BC8            mov ecx, eax
    //    79663C4A    E8 31442100     call WeChatWi.79878080


    __asm {
        pushad
        pushfd


        lea ecx, buff
        call call_1
        lea eax, buff
        push eax
        lea esi, wxid
        push esi
        call call_2
        mov ecx, eax
        call call_3

        popfd
        popad

    }

    std::string sValue = "";
    char cValue[0x1000] = { 0 };
    memcpy_s(cValue, 0x1000, *buff.group_wxid, 0x1000);
    sValue = std::string(cValue);

    //MessageBoxA(NULL, cValue, "ok", MB_OK);
    return sValue;


}