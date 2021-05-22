#include "PubLic.h"
#include "pch.h"
#include <iostream>

#include "HWeChat.h"

#include "pch.h"


#include "jsonxx/json.hpp"

DWORD getWeChatwinADD();
void DelRoomMember(std::wstring roomid, std::wstring memberwxid)
{

    
    
    //群ID结构体
    struct RoomIdStruct
    {
        wchar_t* roomid;
        int roomidLen;
        int roomidMaxLen;
        int full = 0;
        int full2 = 0;
    };

    //拿到call的数据地址
    DWORD dwCall1 = getWeChatwinADD() + (0x572AC4E0 - 0x56D20000);
    DWORD dwCall2 = getWeChatwinADD() + (0x56D9CAF0 - 0x56D20000);
    DWORD dwCall3 = getWeChatwinADD() + (0x5701E3D0 - 0x56D20000);

    //组装群ID结构体
    RoomIdStruct roomiddata;
    roomiddata.roomid = (wchar_t*)roomid.c_str();
    roomiddata.roomidLen = (roomid).size() + 1;
    roomiddata.roomidMaxLen = ((roomid).size() + 1) * 2;

    //组装微信ID结构体
    wchar_t wxidbuff[0xD0] = { 0 };
    DWORD* dwBuff = (DWORD*)&wxidbuff;
    dwBuff[0] = (DWORD)memberwxid.c_str();
    dwBuff[1] = (memberwxid).size();
    dwBuff[2] = (memberwxid).size() * 2;
    dwBuff[3] = 0;
    dwBuff[4] = 0;


    wchar_t datatbuffer[0xD0] = { 0 };
    DWORD* dwDatabuf = (DWORD*)&datatbuffer;
    dwDatabuf[0] = (DWORD)&wxidbuff;
    dwDatabuf[1] = dwDatabuf[0] + 0x14;
    dwDatabuf[2] = dwDatabuf[0] + 0x14;

    //161C25
    //这个地方上层
    //7965E445    68 FC99AE7A     push WeChatWi.7AAE99FC; Deleting now, please wait
    //    7965E44A    68 589AAE7A     push WeChatWi.7AAE9A58; ChatRoomMgr
    //    7965E44F    68 D499AE7A     push WeChatWi.7AAE99D4; ChatRoomMgr::doDelMemberFromChatRoom
    //    7965E454    68 A4000000     push 0xA4




    //56D20000
//    56E81C25    83EC 14         sub esp, 0x14
//    56E81C28    8BCC            mov ecx, esp
//    56E81C2A    89A5 5CFEFFFF   mov dword ptr ss : [ebp - 0x1A4] , esp
//    56E81C30    53              push ebx;                    群号

//    0F94296C  0D173148  UNICODE "22552684336@chatroom"
//    0F942970  00000014
//    0F942974  00000014



//    56E81C31    E8 AAA84200     call WeChatWi.572AC4E0


//    56E81C36    57              push edi; WeChatWi.58885310

//    0F9429E4  0FAF9B58           

          //    0FAF9B58  0CBD3EE8  UNICODE "wxid_4zr616ir6fi122"
          //    0FAF9B5C  00000013
          //    0FAF9B60  00000013




//    0F9429E8  0FAF9B6C
//    0F9429EC  0FAF9B6C
//    0F9429F0  0CF174E8
//    0F9429F4  0CF174F0
//    0F9429F8  0CF174F0




//    56E81C37    C645 FC 09      mov byte ptr ss : [ebp - 0x4] , 0x9


//    56E81C3B    E8 B0AEF1FF     call WeChatWi.56D9CAF0
//    56E81C40    8BC8            mov ecx, eax
//    56E81C42    C645 FC 05      mov byte ptr ss : [ebp - 0x4] , 0x5


//    56E81C46    E8 85C71900     call WeChatWi.5701E3D0
//    56E81C4B    C686 88070000 0 > mov byte ptr ds : [esi + 0x788] , 0x1
//    56E81C52    8B46 E0         mov eax, dword ptr ds : [esi - 0x20]
//    56E81C55    8D4E E0         lea ecx, dword ptr ds : [esi - 0x20]
//    56E81C58    6A 01           push 0x1

    __asm
    {
        pushad;
        sub esp, 0x14;
        lea eax, roomiddata.roomid;
        mov ecx, esp;
        push eax;
        call dwCall1;
        lea edi, datatbuffer;
        push edi;
        call dwCall2;
        mov ecx, eax;
        call dwCall3;
        popad;
    }
}




void AddChatroomMember(wchar_t* chatroomwxid, wchar_t* wxid)
{
    //
    //    793E09AD    6A 00           push 0x0
    //    793E09AF    68 B45BE07A     push WeChatWi.7AE05BB4
    //    793E09B4    8D4D D4         lea ecx, dword ptr ss : [ebp - 0x2C]
    //    793E09B7    E8 34BC5000     call WeChatWi.798EC5F0
    //    793E09BC    C745 FC 0200000 > mov dword ptr ss : [ebp - 0x4] , 0x2
    //    793E09C3    8B37            mov esi, dword ptr ds : [edi]
    //    793E09C5    8BBB 7C0F0000   mov edi, dword ptr ds : [ebx + 0xF7C]
    //    793E09CB    3BF7            cmp esi, edi
    //    793E09CD    74 2A           je short WeChatWi.793E09F9
    //    793E09CF    90              nop
    //    793E09D0    8B45 D4         mov eax, dword ptr ss : [ebp - 0x2C]
    //    793E09D3    85C0            test eax, eax
    //    793E09D5    74 06           je short WeChatWi.793E09DD
    //    793E09D7    66 : 8338 00      cmp word ptr ds : [eax] , 0x0
    //    793E09DB    75 05           jnz short WeChatWi.793E09E2
    //    793E09DD    B8 F4A7B37A     mov eax, WeChatWi.7AB3A7F4
    //    793E09E2    50              push eax; wxid
    //    793E09E3    8BCE            mov ecx, esi
    //    793E09E5    E8 36C35000     call WeChatWi.798ECD20
    //    793E09EA    85C0            test eax, eax
    //    793E09EC    0F84 A3000000   je WeChatWi.793E0A95; 未跳
    //    793E09F2    83C6 14         add esi, 0x14
    //    793E09F5    3BF7            cmp esi, edi
    //    793E09F7 ^ 75 D7           jnz short WeChatWi.793E09D0; 未跳
    //    793E09F9    8DB3 780F0000   lea esi, dword ptr ds : [ebx + 0xF78]
    //    793E09FF    8D45 C0         lea eax, dword ptr ss : [ebp - 0x40]
    //    793E0A02    50              push eax
    //    793E0A03    8D8B 880B0000   lea ecx, dword ptr ds : [ebx + 0xB88] ; 群信息
    //    793E0A09    E8 42260100     call WeChatWi.793F3050; call1
    //    793E0A0E    8378 04 00      cmp dword ptr ds : [eax + 0x4] , 0x0
    //    793E0A12    0F9EC0          setle al
    //    793E0A15    84C0            test al, al
    //    793E0A17    75 13           jnz short WeChatWi.793E0A2C; 不能跳
    //    793E0A19    8D8B 880B0000   lea ecx, dword ptr ds : [ebx + 0xB88]
    //    793E0A1F    E8 CC332A00     call WeChatWi.79683DF0; 不需要执行
    //    793E0A24    C645 F3 01      mov byte ptr ss : [ebp - 0xD] , 0x1
    //    793E0A28    84C0            test al, al
    //    793E0A2A    75 04           jnz short WeChatWi.793E0A30; 跳
    //    793E0A2C    C645 F3 00      mov byte ptr ss : [ebp - 0xD] , 0x0; 这行绝对不能执行
    //    793E0A30    8D4D C0         lea ecx, dword ptr ss : [ebp - 0x40] ; room wxid
    //    793E0A33    E8 18BD5000     call WeChatWi.798EC750; call2
    //    793E0A38    807D F3 00      cmp byte ptr ss : [ebp - 0xD] , 0x0
    //    793E0A3C    74 6E           je short WeChatWi.793E0AAC; 未跳
    //    793E0A3E    83EC 14         sub esp, 0x14; 需要执行call3
    //    793E0A41    8D8B 880B0000   lea ecx, dword ptr ds : [ebx + 0xB88]
    //    793E0A47    8BC4            mov eax, esp
    //    793E0A49    8965 E8         mov dword ptr ss : [ebp - 0x18] , esp
    //    793E0A4C    50              push eax
    //    793E0A4D    E8 FE250100     call WeChatWi.793F3050
    //    793E0A52    C645 FC 03      mov byte ptr ss : [ebp - 0x4] , 0x3
    //    793E0A56    A1 E464E07A     mov eax, dword ptr ds : [0x7AE064E4]
    //    793E0A5B    A8 01           test al, 0x1
    //    793E0A5D    75 22           jnz short WeChatWi.793E0A81; 跳
    //    793E0A5F    83C8 01 or eax, 0x1
    //    793E0A62    A3 E464E07A     mov dword ptr ds : [0x7AE064E4] , eax
    //    793E0A67    C645 FC 04      mov byte ptr ss : [ebp - 0x4] , 0x4
    //    793E0A6B    E8 B0D02700     call WeChatWi.7965DB20
    //    793E0A70    68 10648D7A     push WeChatWi.7A8D6410
    //    793E0A75    E8 9B30FD00     call WeChatWi.7A3B3B15
    //    793E0A7A    83C4 04         add esp, 0x4
    //    793E0A7D    C645 FC 03      mov byte ptr ss : [ebp - 0x4] , 0x3
    //    793E0A81    56              push esi; 需要执行call4
    //    793E0A82    B9 D863E07A     mov ecx, WeChatWi.7AE063D8
    //    793E0A87    C645 FC 02      mov byte ptr ss : [ebp - 0x4] , 0x2
    //    793E0A8B    E8 50D72700     call WeChatWi.7965E1E0


    //79360000
    DWORD dwCallAddr1 = getWeChatwinADD() + 0x82530;
    DWORD dwCallAddr2 = getWeChatwinADD() + 0x58C5F0;
    DWORD dwCallAddr3 = getWeChatwinADD() + 0x93050;
    DWORD dwCallAddr4 = getWeChatwinADD() + 0x2FE1E0;

    DWORD dwParam = getWeChatwinADD() + 0x1AA5BB4;
    DWORD dwParam2 = getWeChatwinADD() + 0x1AA63D8;

    struct Wxid
    {
        wchar_t* str;
        int strLen = 0;
        int maxLen = 0;
        char file[0x8] = { 0 };
    };

    struct tempChatRoom
    {
        char fill2[0x8] = { 0 };
        wchar_t* str;
        int strLen = 0;
        int maxLen = 0;
        char fill[0x8] = { 0 };
    };

    Wxid wxidStruct = { 0 };
    wxidStruct.str = wxid;
    wxidStruct.strLen = wcslen(wxid) * 2;
    wxidStruct.maxLen = wcslen(wxid) * 4;

    tempChatRoom chatroomStruct = { 0 };
    chatroomStruct.str = chatroomwxid;
    chatroomStruct.strLen = wcslen(chatroomwxid) * 2;
    chatroomStruct.maxLen = wcslen(chatroomwxid) * 4;

    char wxidBuff[0xC] = { 0 };
    char tempWxid[0x14] = { 0 };
    char tempBuff[0x14] = { 0 };

    char* pWxid = (char*)&wxidStruct.str;
    char* pChatRoom = (char*)&chatroomStruct.fill2;

    __asm {
        pushad;

        lea esi, wxidBuff;
        mov ecx, esi;
        mov eax, pWxid;
        push eax;
        call dwCallAddr1;


        push 0;
        push dwParam;
        lea ecx, tempWxid;
        call dwCallAddr2;


        sub esp, 0x14;
        mov ecx, pChatRoom;
        mov eax, esp;
        push eax;
        call dwCallAddr3;

        push esi;
        mov ecx, dwParam2;
        call dwCallAddr4;

        popad;
    }
}
