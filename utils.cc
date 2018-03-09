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

	if(logfile == NULL) logfile = fopen("log.txt", "a");
	if(logfile != NULL) {
		vfprintf(logfile, fmt, args);
		fflush(logfile);
	}

	va_end(args);
	return 0;
}

FILE *infofile;
int info(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	if(infofile == NULL) infofile = fopen("info.txt", "w");
	if(infofile != NULL) {
		vfprintf(infofile, fmt, args);
		fflush(infofile);
	}

	va_end(args);
	return 0;
}

std::string formatA(const char *fmt, ...) {
	int size = 100;
	std::string str;
	va_list ap;

	while(1) {
		str.resize(size);

		va_start(ap, fmt);
		int n = _vsnprintf((char *)str.c_str(), size, fmt, ap);
		va_end(ap);

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
