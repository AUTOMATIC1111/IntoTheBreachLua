#include "lua-functions.h"
#include "utils.h"
#include <windows.h>

int ListDirectoryFull(lua_State *L, int mode) {
	const char *dirname = lua_tostring(L, 1);

	lua_newtable(L);

	WIN32_FIND_DATAA fdFile;
	HANDLE handle = NULL;

	std::string path = formatA("%s\\*.*", dirname);
	if((handle = FindFirstFileA(path.c_str(), &fdFile)) == INVALID_HANDLE_VALUE) {
		return 1;
	}

	int index = 0;
	do {
		if(strcmp(fdFile.cFileName, ".") == 0 || strcmp(fdFile.cFileName, "..") == 0)
			continue;

		int isDir = fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? 1 : 0;
		if(mode != -1 && mode != isDir)
			continue;

		lua_pushnumber(L, index++);
		lua_pushstring(L, fdFile.cFileName);
		lua_settable(L, -3);

		log("  [%s]\n", fdFile.cFileName);

	} while(FindNextFileA(handle, &fdFile));

	FindClose(handle);

	return 1;
}

int ListDirectory(lua_State *L) {
	return ListDirectoryFull(L, -1);
}

int ListDirectoryFiles(lua_State *L) {
	return ListDirectoryFull(L, 0);
}

int ListDirectoryDirs(lua_State *L) {
	return ListDirectoryFull(L, 1);
}

int Messagebox(lua_State *L) {
	const char *text = lua_tostring(L, 1);

	MessageBoxA(NULL, text, "Message", 0);

	return 0;
}
