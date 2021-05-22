#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#define SIGSCANDLL_EXPORTS
#ifdef SIGSCANDLL_EXPORTS
#define GeekX_API __declspec(dllexport) 
#else
#define GeekX_API __declspec(dllimport)
#endif

void OutputDebugPrintf(const char* strOutputString, ...);
GeekX_API DWORD _stdcall GeekXFindPattern(const char* szPattern, DWORD* pmodulBase , int offset = 0);
GeekX_API void _stdcall InitializeSigCopyMemory(DWORD ProcessID, const char* szModule);
GeekX_API void _stdcall FinalizeScan();
