#include "pch.h"
#include "HTools.h"

using namespace std;
#pragma warning(disable:4996)
#pragma comment(lib, "version.lib")

string HTools::GetFileVersion(string filePath) {
	string version = "0.0.0.0";
	if (FileExist(filePath)) {
		VS_FIXEDFILEINFO* fInfo;
		unsigned int fSize = sizeof(VS_FIXEDFILEINFO);
		int size = GetFileVersionInfoSizeA(filePath.c_str(), NULL);
		if (size != 0) {
			size = size * 2;
			char* buff = new char[size];
			if (GetFileVersionInfoA(filePath.c_str(), 0, size, buff)) {
				if (VerQueryValueA(buff, "\\", (void**)&fInfo, &fSize)) {
					sprintf(buff, "%d.%d.%d.%d",
						HIWORD(fInfo->dwFileVersionMS),
						LOWORD(fInfo->dwFileVersionMS),
						HIWORD(fInfo->dwFileVersionLS),
						LOWORD(fInfo->dwFileVersionLS));
					version = buff;
				}
			}
			delete[] buff;
		}
	}
	return version;
}

BOOL HTools::FileExist(std::string file) {
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}

wstring HTools::itow(int i) {
	wstring data;
	wchar_t t[10];
	wmemset(t, 0, 10);
	wsprintf(t, TEXT("%d"), i);
	data = t;
	return data;
}

string HTools::w2s(wstring wstr) {
	string result;
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}

string HTools::wstring2string(wstring wstr) {
	return w2s(wstr);
}

wstring HTools::s2w(string str) {
	wstring result;
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	result.append(buffer);
	delete[] buffer;
	return result;
}

wstring HTools::string2wstring(string str) {
	return s2w(str);
}

const char* HTools::u2g(string str) {
	const char* utf8 = str.c_str();
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* res = new char[len + 1];
	memset(res, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, res, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return res;
}

string& HTools::Replace(string& str, const string& old_value, const string& new_value) {
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		if ((pos = str.find(old_value, pos)) != string::npos) {
			str.replace(pos, old_value.length(), new_value);
		} else { 
			break;
		}
	}
	return str;
}

string HTools::Base64_Encode(const char* data, int len) {
	const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string str;
	unsigned char tmp[4] = { 0 };
	int llen = 0;
	for (int i = 0; i < (int)(len / 3); i++) {
		tmp[1] = *data++;
		tmp[2] = *data++;
		tmp[3] = *data++;
		str += EncodeTable[tmp[1] >> 2];
		str += EncodeTable[((tmp[1] << 4) | (tmp[2] >> 4)) & 0x3F];
		str += EncodeTable[((tmp[2] << 2) | (tmp[3] >> 6)) & 0x3F];
		str += EncodeTable[tmp[3] & 0x3F];
		if (llen += 4, llen == 76) {
			str += "\r\n";
			llen = 0;
		}
	}
	int mod = len % 3;
	if (mod == 1) {
		tmp[1] = *data++;
		str += EncodeTable[(tmp[1] & 0xFC) >> 2];
		str += EncodeTable[((tmp[1] & 0x03) << 4)];
		str += "==";
	} else if (mod == 2) {
		tmp[1] = *data++;
		tmp[2] = *data++;
		str += EncodeTable[(tmp[1] & 0xFC) >> 2];
		str += EncodeTable[((tmp[1] & 0x03) << 4) | ((tmp[2] & 0xF0) >> 4)];
		str += EncodeTable[((tmp[2] & 0x0F) << 2)];
		str += "=";
	}
	return str;
}

string HTools::Base64_Encode(string str) {
	return Base64_Encode(str.c_str(), str.size());
}

string HTools::Base64_Decode(const char* data, int len, int& olen) {
	const char DecodeTable[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			62,
			0, 0, 0,
			63,
			52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
			0, 0, 0, 0, 0, 0, 0,
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
			13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
			0, 0, 0, 0, 0, 0,
			26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
			39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
	};
	string str;
	int index;
	int i = 0;
	while (i < len) {
		if (*data != '\r' && *data != '\n') {
			index = DecodeTable[*data++] << 18;
			index += DecodeTable[*data++] << 12;
			str += (index & 0x00FF0000) >> 16;
			olen++;
			if (*data != '=') {
				index += DecodeTable[*data++] << 6;
				str += (index & 0x0000FF00) >> 8;
				olen++;
				if (*data != '=') {
					index += DecodeTable[*data++];
					str += index & 0x000000FF;
					olen++;
				}
			}
			i += 4;
		} else {
			data++;
			i++;
		}
	}
	return str;
}

string HTools::Base64_Decode(string data, int& olen) {
	return Base64_Decode(data.c_str(), data.size(), olen);
}

std::wstring HTools::RegReadView(HKEY root, LPCWSTR path, LPCWSTR key, DWORD type) {
	wstring value(TEXT(""));
	HKEY hKey;
	if (RegOpenKey(root, path, &hKey) == ERROR_SUCCESS) {
		wchar_t buf[MAX_PATH];
		wmemset(buf, 0, MAX_PATH);
		DWORD data = MAX_PATH * sizeof(wchar_t);
		if (RegQueryValueEx(hKey, key, 0, &type, (LPBYTE)buf, &data) == ERROR_SUCCESS) {
			value = buf;
		}
		RegCloseKey(hKey);
	}
	return value;
}

DWORD HTools::ReadInt(DWORD address) {
	DWORD intValue = 0;
	intValue = *(DWORD*)address;
	return intValue;
}

string HTools::ReadAsciiString(DWORD address) {
	string sValue = "";
	char cValue[0x1000] = { 0 };
	memcpy(cValue, (const void*)address, 0x1000);
	sValue = string(cValue);
	return sValue;
}

wstring HTools::ReadUnicodeString(DWORD address) {
	wstring value;
	int slen = (int)ReadInt(address + 0x4);
	DWORD str = ReadInt(address);
	if (str == NULL || slen == 0) {
		return value;
	}
	wchar_t* buffer = NULL;
	do {
		buffer = new wchar_t[slen + 1];
	} while (buffer == NULL);
	wmemset(buffer, 0, slen + 1);
	wmemcpy(buffer, (const wchar_t*)str, slen);
	buffer[slen] = '\0';
	value.append(buffer);
	delete[] buffer;
	return value;
}

typedef struct tagWNDINFO {
	DWORD dwProcessId;
	HWND hWnd;
} WNDINFO, * LPWNDINFO;

BOOL CALLBACK YourEnumProc(HWND hWnd, LPARAM lParam) {
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	LPWNDINFO pInfo = (LPWNDINFO)lParam;
	if (dwProcessId == pInfo->dwProcessId) {
		pInfo->hWnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND HTools::GetProcessWnd(DWORD pid) {
	WNDINFO wi;
	wi.dwProcessId = pid;
	wi.hWnd = NULL;
	EnumWindows(YourEnumProc, (LPARAM)&wi);
	return wi.hWnd;
}
