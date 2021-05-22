#pragma once
#include <string>

#define		WX_VERSION		"3.1.0.41"

#define FIVE 5

class HUtil {
public:
	HUtil();
	~HUtil();

	DWORD Offset(DWORD offset);

	void OpenConsole();
	void CloseConsole();

private:
	DWORD mBase = NULL;

	FILE* mConsoleOut;
	std::streambuf* mConsoleOutBackup;
	BOOL mConsoleOpen = FALSE;

public:
	static std::string GetWeChatVersion();
};

