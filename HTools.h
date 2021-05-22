#pragma once
#include <string>
#include <Ntsecapi.h>



class HTools {


public:
	static std::string GetFileVersion(std::string filePath);
	static BOOL FileExist(std::string file);

	static std::wstring itow(int i);
	static std::string w2s(std::wstring wstr);
	static std::string wstring2string(std::wstring wstr);
	static std::wstring s2w(std::string str);
	static std::wstring string2wstring(std::string str);
	static const char* u2g(std::string str);
	static std::string& Replace(std::string& str, const std::string& old_value, const std::string& new_value);

	static std::string Base64_Encode(const char* data, int len);
	static std::string Base64_Encode(std::string str);
	static std::string Base64_Decode(const char* data, int len, int& olen);
	static std::string Base64_Decode(std::string data, int& olen);

	static std::wstring RegReadView(HKEY root, LPCWSTR path, LPCWSTR key, DWORD type = REG_SZ);

	static DWORD ReadInt(DWORD address);
	static std::string ReadAsciiString(DWORD address);
	static std::wstring ReadUnicodeString(DWORD address);

	static HWND GetProcessWnd(DWORD pid);
};

