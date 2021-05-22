#include "PubLic.h"
#include "pch.h"
#include <iostream>
#include "HUtil.h"
#include "Init_Match_Pattern.h"
#include <winsock2.h>
#include <Windows.h>
#include <thread>
#include "jsonxx/json.hpp"
#include "ZZHook.h"
#include "HWeChat.h"
#include "cvtcode.hpp"
#define Log(message) std::cout<<message<<std::endl
#pragma warning(disable:4996)

// jsonxx    https://github.com/Nomango/jsonxx
#pragma comment(lib, "ws2_32.lib")


//公共数据
extern jsonxx::json Friend_List;
SOCKET servSock;
SOCKADDR clntAddr;
SOCKET clntSock ;
UINT Data_length = 1024;

void Send_Data(std::string msg);

void SendMsg(std::wstring wxid, std::wstring message);
VOID Send_msg(wchar_t* wxid_Send, wchar_t* message_Send);
void SendXmlCard(std::wstring RecverWxid, std::wstring SendWxid, std::wstring NickName);
BOOL GetUserInfoByWxid(std::wstring wxid, WxUserInfo* info);
VOID Ergodic(const char* prefix, DWORD start, DWORD end);
void Verify_Add_Frind(std::wstring wxid, std::wstring msg);
void DelRoomMember(std::wstring roomid, std::wstring memberwxid);
void AddChatroomMember(wchar_t* chatroomwxid, wchar_t* wxid);
std::string Get_Group_Mem_Wxid(std::wstring RoomWxid);

void Msg_main();



DWORD getWeChatwinADD();
//SOCKET Srever, Client; //创建服务端 客户端套接字
//bool Socket_Init(char* IP, int Port);//初始化
VOID Receive_Data(SOCKET clientSock);//接收数据
//void SendMsg(char* pszSend);//发送数据
//
VOID Receive_Data(SOCKET clientSock)
{
    //接收客户端请求
    char StrBuf[1024] = { 0 };//数据缓冲区
    char data_length_buf[1024] = { 0 };
    int data_lenth = 0;
    while (true)
    {

        std::string Reveved_Data = "";
        int res = 0;
        data_lenth = 0;
        res = recv(clntSock, data_length_buf, 1024, 0);
        if (res < 0)
        {
            Log(WSAGetLastError());
            closesocket(clntSock);
            break;
        }
        data_lenth = atoi(data_length_buf);
        //Reveved_Data.resize(data_lenth);
        Reveved_Data.clear();
        //Log("Data_length" << data_length_buf);
        do
        {
            res = 0;
            res = recv(clntSock, StrBuf, 512, 0);
            Log(sizeof(StrBuf));
            data_lenth -= res;
            //Reveved_Data.append(StrBuf);
            Reveved_Data += StrBuf;
        } while (data_lenth > 0);

        /*Log(Reveved_Data);
        Log(Reveved_Data.length());*/
        //将python端发送的内容解析为json格式 
        

      /*  Json::Reader reader;
        Json::Value root;
        Json::FastWriter writer;*/
        //root["encoding"] = "11111";
        try
        {
            /* reader.parse(Reveved_Data, root);*/
             //
             //string tmp = writer.write(root["type"]);
            jsonxx::json js_content = jsonxx::json::parse(Reveved_Data);
            int type = js_content["type"].as_int();
            switch (type)
            {
            case 1: {        
                Log("发送消息");
                std::wstring wxid = String2WString(js_content["wxid"].as_string());
                std::wstring msg = String2WString(js_content["msg"].as_string());
             /*   wchar_t* wxid_Send = (wchar_t*)wxid.c_str();
                wchar_t* message_Send = (wchar_t*)msg.c_str();*/
                std::wcout << wxid << L"  --->  " << msg << std::endl;
                SendMsg(wxid, msg);
                //Send_msg(wxid_Send,message_Send);
                break;
            }
            case 2:{//发送名片
                //{"type":2, "wxid" : "filehelper", "source" : "wxid_4zr616ir6fi122", "NickName" : "大标题"}
                std::wstring RecverWxid = String2WString(js_content["wxid"].as_string());
                std::wstring SendWxid= String2WString(js_content["source"].as_string());
                std::wstring NickName= String2WString(js_content["NickName"].as_string());
                SendXmlCard(RecverWxid, SendWxid, NickName);
                break;
            }
            case 3: {//通过wxid获取好友详细信息
                std::wstring wxid = String2WString(js_content["wxid"].as_string());
                //char top[0x8];
                //WxString wxid;
                //WxString account;
                //WxString vData;
                //int un_0;
                //int un_1;
                //char un_2[0x18];
                //WxString name;
                //char un_3[0x28];
                //int un_4;
                //WxString nameUpper;
                //WxString nameUn;
                //char un_5[0x28];
                //WxString pic;
                //WxString img;
                //char* md5;
                //char un_6[0xC];
                //int un_7;
                //int addSource;
                //char un_8[0x2AC];
                //std::wstring wxid = L"wxid_918vi9aqhhx422";
                WxUserInfo info = { 0 };
                if (GetUserInfoByWxid(wxid, &info)) {
                    jsonxx::json DetailInfo;
                    DetailInfo["name"] = uc2u8(info.name.pstr);
                    Send_Data(DetailInfo.dump());
                    //std::wcout << info.name.pstr << std::endl;
                }
                break;
            }
            case 4: {//遍历二叉树获取好友列表
                //63F40000
                //0x659C71AC   [0x659C71AC]
                //    642B85B0 / $  56            push esi
                //    642B85B1 | .  68 30369D65   push WeChatWi.659D3630; / pCriticalSection = WeChatWi.659D3630
                //    642B85B6 | .  33F6 xor esi, esi; |
                //    642B85B8 | .FF15 60924D65 call dword ptr ds : [<&KERNEL32.EnterCriti>; \EnterCriticalSection
                //    642B85BE | .  66:90         nop
                //    642B85C0 | > A0 AA719C65 / mov al, byte ptr ds : [0x659C71AA]
                //    642B85C5 | .  84C0 | test al, al
                //    642B85C7 | .  74 6E | je short WeChatWi.642B8637
                //    642B85C9 | .  833D AC719C65 > | cmp dword ptr ds : [0x659C71AC] , 0x0
                //    642B85D0 | .  74 1B | je short WeChatWi.642B85ED
                //    642B85D2 | .  46 | inc esi
                //    642B85D3 | .  83FE 01 | cmp esi, 0x1
                //    642B85D6 | . ^ 7C E8         \jl short WeChatWi.642B85C0
                //    642B85D8 | .  68 30369D65   push WeChatWi.659D3630; / pCriticalSection = WeChatWi.659D3630
                //    642B85DD | .FF15 5C924D65 call dword ptr ds : [<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
                //    642B85E3 | .A1 AC719C65   mov eax, dword ptr ds : [0x659C71AC]
                //    642B85E8 | .  83C0 28       add eax, 0x28
                //    642B85EB | .  5E            pop esi;  WeChatWi.642657F4
                //    642B85EC | .C3            retn


                DWORD friendList_base = HTools::ReadInt(getWeChatwinADD() + 0x1A871AC);
                DWORD m_friendList_base = friendList_base + 0x28 + 0x8C;
                DWORD ListTop = HTools::ReadInt(m_friendList_base);

                Ergodic("base", HTools::ReadInt(ListTop + 0x4), ListTop);

                Send_Data(Friend_List.dump());
            }
            case 5: {//踢出群成员
                std::wstring roomid = String2WString(js_content["roomid"].as_string());
                std::wstring memberwxid = String2WString(js_content["memberwxid"].as_string());
                DelRoomMember(roomid, memberwxid);
            }
            case 6: { //被好友删除后，发送  验证添加好友       
                std::wstring wxid = String2WString(js_content["wxid"].as_string());
                std::wstring msg = String2WString(js_content["msg"].as_string());
                Verify_Add_Frind(wxid, msg);
                break;
            }
            case 7: {//增加群成员
                std::wstring chatroomwxid = String2WString(js_content["chatroomwxid"].as_string());
                std::wstring wxid = String2WString(js_content["wxid"].as_string());

                AddChatroomMember((wchar_t*)chatroomwxid.c_str(),  (wchar_t*)wxid.c_str());

                break;
            }
            case 8:{
                jsonxx::json J_Mem_Wxid;
                std::wstring chatroomwxid = String2WString(js_content["chatroomwxid"].as_string());
                std::string Mem_Wxid=Get_Group_Mem_Wxid(chatroomwxid);
                J_Mem_Wxid["All_wxid"] = Mem_Wxid;
                Send_Data(J_Mem_Wxid.dump());
                break;
                  
            }
            default:
                break;
            }
            // Log(tmp);
        }
        catch (const std::exception&)
        {
            //Log("Reveved_Data-->  " << Reveved_Data);
            Log("解析成json失败");
        }

        //Log()
        memset(data_length_buf, 0, sizeof(data_length_buf));
        memset(StrBuf, 0, sizeof(StrBuf));
        //RecvAll(clntSock, StrBuf, MAX_PATH);

        //printf("收到的消息:\n\n %s \n", Reveved_Data);
    }

}

VOID Send_Data(std::string msg)
{
    //const char* str = u8"success lalalal";
    //std::string msg = WString2String(data);
    int optVal;
    int optLen = sizeof(int);
    /*  if (getsockopt(clntSock, SOL_SOCKET, SO_ACCEPTCONN, (char*)&optVal, &optLen) != SOCKET_ERROR)
        printf("SockOpt Value: %ld\n", optVal);*/
    char msg_length[16] = { 0 };
    itoa(msg.length(), msg_length, 16);
    send(clntSock, msg_length, strlen(msg_length), NULL);
    int iResult = send(clntSock, msg.c_str(), msg.length(), NULL);
    Log("sended_length     " << iResult);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(clntSock);
        WSACleanup();
    }
}





void Start_Socket() {
    setlocale(LC_ALL, "chs");

    HUtil Hutil;
    Hutil.OpenConsole();
    //HANDLE hProcessHandle;
    //hProcessHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE,
    //    FALSE, GetCurrentProcessId());
    //int Match_res= Main_Match_Pattern();
    //if (!Match_res)
    //{

    //    return;
    //}
    Main_Match_Pattern();
    Msg_main();
    //MessageBoxA(NULL, "进入Start_Socket", NULL, MB_OK);




    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //绑定套接字
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port =htons(8989);  //端口
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //进入监听状态
    Log("等待连接....");
    listen(servSock, 20);
    while (true)
    {
        //创建线程
       // thread  CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Receive_Data, NULL, NULL, NULL);
        int nSize = sizeof(SOCKADDR);
        clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

        if (clntSock != INVALID_SOCKET)
        {
            Log(inet_ntoa(sockAddr.sin_addr) << "连接");
            //向客户端发送数据
            //std::thread th2(Send_Data, clntSock);

           /* std::wstring ucData = LR"({"from_group_wxid":"wxid_qnd3hknyxdq222","msg":"你好","wxid":"25096554173@chatroom"})";
            std::string u8Data = uc2u8(ucData);
            Send_Data(u8Data);*/


            std::thread th1(Receive_Data, clntSock);

            th1.detach();
            //th2.detach();
            memset(&sockAddr, 0, sizeof(sockAddr));
        }

        //Log("连接断开");
    }
    //终止 DLL 的使用
    WSACleanup();
}