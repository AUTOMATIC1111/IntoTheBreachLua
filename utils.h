#ifndef __UTILS__H__
#define __UTILS__H__

#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <windows.h>
#include <string>
#include <functional>

int log(char *fmt, ...);
int error(char *fmt, ...);

/// Displays message box with error and halts the game
void panic(const std::string & message);

std::string format(const char *fmt, ...);
std::string formatv(const char *fmt, va_list ap);

std::wstring s2ws(const std::string& s);
std::string ws2s(const std::wstring& s);
std::wstring cs2ws(const char *s);
std::string cws2s(const TCHAR *s);

void listDir(const std::string & path, std::function<void(const std::string &s, bool isDir)>);

#endif
