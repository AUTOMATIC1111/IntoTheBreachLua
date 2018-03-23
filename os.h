#ifndef __OS_LUA_H__
#define __OS_LUA_H__

#include <windows.h>
#include <string>

namespace OS {

std::string getKnownFolder(int csild);

bool isshiftdown();

double mtime(const std::string filename);

std::string getKnownFolder(int csild);
void mkdir(std::string path);

void log(const std::string & line);


}

#endif
