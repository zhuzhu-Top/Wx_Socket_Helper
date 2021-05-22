	//@Unicode To Utf-8
	static inline std::string uc2u8(std::wstring unicode)
	{
		int len = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
		char* utf8 = (char*)malloc(len);
		memset(utf8, 0, len);
		WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), -1, utf8, len, NULL, NULL);
		std::string str(utf8);
		free(utf8);
		return str;
	}
	//@Utf-8 To Unicode
	static inline std::wstring u82uc(const std::string utf8)
	{
		if (utf8.empty())
		{
			return std::wstring();
		}

		int len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
		wchar_t *unicode = (wchar_t*)malloc((len * sizeof(wchar_t)));
		wmemset(unicode, 0, len);
		MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, (LPWSTR)unicode, len);
		std::wstring str(unicode);
		free(unicode);
		return str;
	}
	//@Gbk To Utf-8
	static inline std::string gbk2u8(const std::string gbk)
	{
		//Gbk To Unicode  
		int len = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, NULL, 0);
		wchar_t* unicode = (wchar_t*)malloc((len * sizeof(wchar_t)));
		wmemset(unicode, 0, len);
		MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, unicode, len);

		//Unicode To Utf-8
		len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
		char * utf8 = (char*)malloc((len * sizeof(char)));
		memset(utf8, 0, len);
		WideCharToMultiByte(CP_UTF8, 0, unicode, -1, utf8, len, NULL, NULL);

		std::string str(utf8);
		free(unicode);
		free(utf8);
		return str;
	}
	//@UTF-8 To GBK  
	static inline std::string u82gbk(const std::string utf8)
	{
		//Utf-8 To Unicode  
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
		wchar_t* unicode = (wchar_t*)malloc((len * sizeof(wchar_t)));
		wmemset(unicode, 0, len);
		MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, unicode, len);

		//Unicode To Gbk
		len = WideCharToMultiByte(CP_ACP, 0, unicode, -1, NULL, 0, NULL, NULL);
		char* gbk = (char*)malloc((len * sizeof(char)));
		memset(gbk, 0, len);
		WideCharToMultiByte(CP_ACP, 0, unicode, -1, gbk, len, NULL, NULL);

		std::string str(gbk);
		free(unicode);
		free(gbk);
		return str;
	}
	//@Gbk To Unicode
	static inline std::wstring gbk2uc(const std::string gbk)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, NULL, 0);
		wchar_t* unicode = (wchar_t*)malloc((len * sizeof(wchar_t)));
		wmemset(unicode, 0, len);
		MultiByteToWideChar(CP_ACP, 0, gbk.c_str(), -1, unicode, len);

		std::wstring str(unicode);
		free(unicode);
		return str;
	}
	//@Unicode To Gbk
	static inline std::string uc2gbk(const std::wstring unicode)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
		char* gbk = (char*)malloc((len * sizeof(char)));
		WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), -1, gbk, len, NULL, NULL);

		std::string str(gbk);
		free(gbk);
		return str;
	}
	//@Unicode To Utf-8
	static inline int uc2u8(__out char* utf8, const wchar_t* unicode)
	{
		int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, unicode, -1, utf8, len, NULL, NULL);
		return len;
	}
	//@Utf-8 To Unicode
	static inline int u82uc(__out wchar_t* unicode, const char* utf8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0); //-1 include '\0'
		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, (LPWSTR)unicode, len);
		return len;
	}