#include "PubLic.h"
#include "pch.h"
#include "HTools.h"
#include "ZZHook.h"
#include <string>
#include <winsock2.h>
//#include <json\json.h>
#include "cvtcode.hpp"
#include "jsonxx/json.hpp"
#pragma warning(disable:4996)
DWORD getWeChatwinADD();
VOID Send_Data(std::string data);
std::string WString2String(const std::wstring& ws);
extern SOCKET clntSock;


#define IS_USE_OUTPUT_DEBUG_PRINT   1

#if  IS_USE_OUTPUT_DEBUG_PRINT 

#define  OUTPUT_DEBUG_PRINTF(str)  OutputDebugPrintf(str)
void OutputDebugPrintf(const char* strOutputString, ...)
{
#define PUT_PUT_DEBUG_BUF_LEN   1024
    char strBuffer[PUT_PUT_DEBUG_BUF_LEN] = { 0 };
    va_list vlArgs;
    va_start(vlArgs, strOutputString);
    _vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);  //_vsnprintf_s  _vsnprintf
    //vsprintf(strBuffer,strOutputString,vlArgs);
    va_end(vlArgs);
    OutputDebugStringA(strBuffer);  //OutputDebugString    // OutputDebugStringW
}
#else 
#define  OUTPUT_DEBUG_PRINTF(str) 
#endif

LPCWSTR GetMsgByAddress(DWORD memAddress)
{
    //获取字符串长度
    DWORD msgLength = *(DWORD*)(memAddress + 4);
    if (msgLength == 0)
    {
        WCHAR* msg = new WCHAR[1];
        msg[0] = 0;
        return msg;
    }

    WCHAR* msg = new WCHAR[msgLength + 1];

    ZeroMemory(msg, msgLength + 1);
    //复制内容
    wmemcpy_s(msg, msgLength + 1, (WCHAR*)(*(DWORD*)memAddress), msgLength + 1);
    return msg;
}

int My_Msg_Call_Back(DWORD EDI, DWORD ESI, DWORD EBP, DWORD ESP, DWORD EBX, DWORD EDX, DWORD ECX, DWORD EAX) {
    ESP += 0x24;
    //MessageBoxA(NULL, (const char *)HTools::ReadUnicodeString(*(DWORD*)(*(DWORD*)EBX + 0x68)).c_str(), NULL, MB_OK);
    //std::cout << HTools::ReadUnicodeString(*(DWORD*)(*(DWORD*)EBX + 0x68)).c_str() << std::endl;
    //GetMsgByAddress(*    (DWORD *)(    *(DWORD*)E BX + 0x68   )    )
    try
    {
        jsonxx::json js_Data;
        //WCHAR* msgType = new WCHAR[8];
        //ZeroMemory(msgType,8 );
        //wmemcpy_s(msgType, 4, (WCHAR*)(*(DWORD*)EBX + 0x30), 4);

        DWORD msgType = HTools::ReadInt(*(DWORD*)EBX + 0x30);
        //DWORD SourceType= HTools::ReadInt(*(DWORD*)EBX + 0x88);
        DWORD From_Group= HTools::ReadInt(*(DWORD*)EBX + 0x168);  //168出大于零说明有群消息发送者的wxid,说明是群消息
        if (From_Group!=0)
        {
            //来自群的消息
            js_Data["from_group_wxid"]= uc2u8( GetMsgByAddress(*(DWORD*)EBX + 0x164));
        }

        //00000136   公众号
        switch (msgType)
        {
        case 0x01:   //文字消息

            break;
        case 0x03:    //图片

            break;
        case 0x2F:   //视频


            break;

        case 0x30:   //位置

            break;
        case 0x31:   //语音消息


            break;
            
        default:
            break;
        }   
       // wchar_t* msgType= (WCHAR*)(*(DWORD*)EBX + 0x30)

        std::wstring msg_content = GetMsgByAddress(*(DWORD*)EBX + 0x68);
        std::wstring wxid = GetMsgByAddress(*(DWORD*)EBX + 0x40);

        //MessageBoxW(NULL, tmp.c_str(), NULL, MB_OK);
        std::wcout << msgType << std::endl;


        js_Data["wxid"] = uc2u8(wxid);
        js_Data["msg"] = uc2u8(msg_content);

        std::string Socket_Data = js_Data.dump();

        if (clntSock != INVALID_SOCKET)
        {
            Send_Data(Socket_Data);
        }

    }
    catch (const std::exception&)
    {
        MessageBoxA(NULL, "错误", "ok", MB_OK);
    }
    //

    return 1;
}


void Msg_main() {

    DWORD WechatWindllADD = getWeChatwinADD();
    extern DWORD Recv_Msg_ADD;
    //
    std::cout << "Msg_main   Recv_Msg_ADD   地址   " <<Recv_Msg_ADD << std::endl;
    if (Recv_Msg_ADD < 0x100)
    {
        std::cout << "Recv_Msg_ADD 地址匹配失败" << std::endl;
        return;
    }

    Hook* Msg_hook = new Hook(Recv_Msg_ADD+0x4);
    void* lpAddr = VirtualAlloc(
        NULL,
        1,
        MEM_COMMIT,
        PAGE_EXECUTE_READWRITE
    );
    if (lpAddr == NULL) {
        printf_s("Alloc error!");
        return;
    }
    Msg_hook->StartHook(lpAddr, (DWORD)My_Msg_Call_Back);
}