// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "socketMain.h"
#pragma warning(disable:4996)
#include <iostream>

VOID Send_Data(std::string data);
void Start_Socket();
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
        //MessageBoxA(NULL, "DLL_PROCESS_ATTACH", NULL, MB_OK);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Start_Socket, hModule, 0, NULL);
         }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        //MessageBox(NULL, L"over", L"over", MB_OK);
        break;
    }
    return TRUE;
}

//把发送数据的代码领出来写再这
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//    //你来 注释掉
//    Start_Socket();
//
//    return 0;
//}
