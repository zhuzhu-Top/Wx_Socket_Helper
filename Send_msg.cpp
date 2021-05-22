#include "PubLic.h"
#include "pch.h"
#include <iostream>
DWORD getWeChatwinADD();

extern DWORD Send_Normal_msg_ADD;

struct wxString
{
	wchar_t* pStr;
	int strLen;
	int strMaxLen;
	char fillbuff[0x8];
};

typedef struct _WXSTRING {
    wchar_t* pstr;
    int len;
    int maxLen;
    int fill1 = 0;
    int fill2 = 0;
} WxString;
void SendMsg(std::wstring wxid, std::wstring message) {
    WxString to = { 0 };
    WxString text = { 0 };

    to.pstr = (wchar_t*)wxid.c_str();
    to.len = wxid.size();
    to.maxLen = wxid.size() * 2;

    text.pstr = (wchar_t*)message.c_str();
    text.len = message.size();
    text.maxLen = message.size();

    char buff[0x20] = { 0 };
    char buff_2[0x500] = { 0 };

    DWORD sendCall = getWeChatwinADD() + 0x3B50E0;

    __asm {
        pushad
        pushfd

        push 0x1
        lea edi, buff
        push edi
        lea ebx, text
        push ebx
        lea edx, to
        lea ecx, buff_2
        call sendCall
        add esp, 0xc

        popfd
        popad
    }
}

//自己写的发送消息    可以用来当作参考
//VOID Send_msg(wchar_t* wxid_Send, wchar_t* message_Send) {
//    
//
//
//	//DWORD Send_call = getWeChatwinADD() + Send_Normal_msg_ADD;     //偏移
//	DWORD Send_call = getWeChatwinADD() + 0x3B50E0;     //偏移
//	//组装需要的数据格式
//	wxString pWxid = { 0 };
//	pWxid.pStr = wxid_Send;
//	pWxid.strLen = wcslen(wxid_Send);                     //wcslen 获取宽字符版本（unicode）的长度
//	pWxid.strMaxLen = wcslen(wxid_Send) * 2;
//
//	wxString pMessage = { 0 };
//	pMessage.pStr = message_Send;
//	pMessage.strLen = wcslen(message_Send);
//	pMessage.strMaxLen = wcslen(message_Send) * 2;
//
//	//取出内容的地址
//	char* asmWxid = (char*)&pWxid.pStr;
//
//	char* asmMessage = (char*)&pMessage.pStr;
//	char buff[0x87C] = { 0 };   //设置缓冲区
//	char buff_2[0x87C] = { 0 };   //设置缓冲区
//
//
//	/*
//mov edx,dword ptr ss:[ebp-0x50]          ; wxid
//lea eax,dword ptr ds:[ebx+0x14]          ; 0
//push 0x1                                 ; 1
//push eax                                 ; 0
//push ebx                                 ; 聊天内容
//lea ecx,dword ptr ss:[ebp-0x87C]
//call WeChatWi.614E9BF0                   ; 发送聊天消息
//
//ebx  ==1160698C
//
//1160698C  121639D8  UNICODE "333333333"
//11606990  00000009
//11606994  00000009
//11606998  00000000
//1160699C  00000000
//6A 01           push 0x1
//57              push edi                                 ; 缓冲区
//53              push ebx                                 ; 消息
//8D95 78FFFFFF   lea edx,dword ptr ss:[ebp-0x88]          ; wxid
//8D8D 58FAFFFF   lea ecx,dword ptr ss:[ebp-0x5A8]
//E8 70862A00     call WeChatWi.7AF750E0                   ; 发送文本消息
//	*/
//    //MessageBoxA(NULL, "OK", "Ok", MB_OK);
//	__asm {
//        pushad
//        pushfd
//
//        push 0x1
//        lea edi, buff_2
//        push edi
//		mov ebx, asmMessage
//		push ebx
//        mov edx, asmWxid             //wxid
//		lea ecx, buff
//		call Send_call
//		add esp, 0xC
//
//        popfd
//        popad
//	}
//};

void SendXmlCard(std::wstring RecverWxid, std::wstring SendWxid, std::wstring NickName)
{


    WxString pWxid = { 0 };
    WxString pXml = { 0 };
    wchar_t xml[0x2000] = { 0 };
    pWxid.pstr = (wchar_t*)RecverWxid.c_str();
    pWxid.len = RecverWxid.size();
    pWxid.maxLen = RecverWxid.size() * 2;

    swprintf_s(xml, L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/0\" smallheadimgurl=\"http://wx.qlogo.cn/mmhead/ver_1/7IiaGRVxyprWcBA9v2IA1NLRa1K5YbEX5dBzmcEKw4OupNxsYuYSBt1zG91O6p07XlIOQIFhPCC3hU1icJMk3z28Ygh6IhfZrV4oYtXZXEU5A/132\" username=\"%s\" nickname=\"%s\" fullpy=\"?\" shortpy=\"\" alias=\"%s\" imagestatus=\"3\" scene=\"17\" province=\"北京\" city=\"中国\" sign=\"\" sex=\"2\" certflag=\"0\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"0\" regionCode=\"CN_BeiJing_BeiJing\" />", (wchar_t*)SendWxid.c_str(), (wchar_t*)NickName.c_str(), (wchar_t*)SendWxid.c_str());
    pXml.pstr = xml;
    pXml.len = wcslen(xml);
    pXml.maxLen = wcslen(xml) * 2;

    char* asmWxid = (char*)&pWxid.pstr;
    char* asmXml = (char*)&pXml.pstr;
    char buff[0x400] = { 0 };
    DWORD callAdd = (DWORD)GetModuleHandle(L"WeChatWin.dll") + 0x3B50E0;

    //typedef int(__fastcall* SendXml)(char buf[], char *wxid, char* xmlCard, DWORD, DWORD);
    //SendXml(buff,asmWxid, asmXml, 0x0, 0x2A);

     //push 0x2A;                                 0x2A
    //lea eax, dword ptr ss : [ebp - 0x28]
    //mov edx, esi;                          对方的wxid   
    //push 0x0; 0                             0
    //push eax;                               卡片xml
    //lea ecx, dword ptr ss : [ebp - 0x284]   缓冲区
    //call WeChatWi.79E950E0
    __asm {
        mov eax, asmXml
        push 0x2A
        mov edx, asmWxid
        push 0x0
        push eax
        lea ecx, buff
        call callAdd
        add esp, 0xC
    }
}