#include "utils.h"
#include <windows.h>
#include <stdarg.h>
#include <tchar.h>
#include <stdio.h>
#include <string>

FILE *logfile;
int log(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	if(logfile == NULL) logfile = fopen("log.txt", "w");
	if(logfile != NULL) {
		vfprintf(logfile, fmt, args);
		fflush(logfile);
	}

	va_end(args);
	return 0;
}

FILE *errorfile;
int error(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	if(errorfile == NULL) errorfile = fopen("error.txt", "w");
	if(errorfile != NULL) {
		vfprintf(errorfile, fmt, args);
		fflush(errorfile);
	}

	va_end(args);
	return 0;
}

void panic(const std::string & message) {
	error("%s\n", message.c_str());

	MessageBoxW(NULL, s2ws(message).c_str(), L"Error", MB_OK);
}

std::string format(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	std::string res = formatv(fmt, ap);
	va_end(ap);
	return res;
}

std::string formatv(const char *fmt, va_list ap) {
	int size = 100;
	std::string str;

	while(1) {
		str.resize(size);

		int n = _vsnprintf((char *)str.c_str(), size, fmt, ap);

		if(n > -1 && n < size) {
			str.resize(n);
			return str;
		}

		if(n > -1)
			size = n + 1;
		else
			size *= 2;
	}
	return str;
}

std::wstring s2ws(const std::string& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, 0, 0);
	std::wstring r(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, &r[0], len);
	r.resize(len - 1);
	return r;
}

std::string ws2s(const std::wstring& s) {
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, 0, 0, 0, 0);
	std::string r(len, '\0');
	WideCharToMultiByte(CP_UTF8, 0, s.c_str(), slength, &r[0], len, 0, 0);
	r.resize(len - 1);
	return r;
}
std::wstring cs2ws(const char *s) {
	int len;
	int slength = (int)strlen(s) + 1;
	len = MultiByteToWideChar(CP_UTF8, 0, s, slength, 0, 0);
	std::wstring r(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, s, slength, &r[0], len);
	r.resize(len - 1);
	return r;
}

std::string cws2s(const TCHAR *s) {
	int len;
	int slength = (int)_tcslen(s) + 1;
	len = WideCharToMultiByte(CP_UTF8, 0, s, slength, 0, 0, 0, 0);
	std::string r(len, '\0');
	WideCharToMultiByte(CP_UTF8, 0, s, slength, &r[0], len, 0, 0);
	r.resize(len - 1);
	return r;
}

void listDir(const std::string & path, std::function<void(const std::string &s, bool isDir)> func) {
	WIN32_FIND_DATAA fdFile;
	HANDLE handle = NULL;

	std::string mask = path + "\\*.*";
	if((handle = FindFirstFileA(mask.c_str(), &fdFile)) == INVALID_HANDLE_VALUE) {
		return;
	}

	int index = 0;
	do {
		if(strcmp(fdFile.cFileName, ".") == 0 || strcmp(fdFile.cFileName, "..") == 0)
			continue;

		bool isDir = fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? true : false;
		std::string fullpath = path + "/" + fdFile.cFileName;

		func(fullpath, isDir);

		if(isDir)
			listDir(fullpath.c_str(), func);

	} while(FindNextFileA(handle, &fdFile));

	FindClose(handle);
}
