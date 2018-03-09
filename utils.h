#ifndef __UTILS__H__
#define __UTILS__H__

#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <windows.h>
#include <string>

int log(char *fmt, ...);
int info(char *fmt, ...);

std::string formatA(const char *fmt, ...);

#endif
