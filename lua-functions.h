#ifndef __LUA__FUNCTIONS__H__
#define __LUA__FUNCTIONS__H__

#include "lua.h"
#include "lauxlib.h"

int ListDirectory(lua_State *L);
int ListDirectoryFiles(lua_State *L);
int ListDirectoryDirs(lua_State *L);

int Messagebox(lua_State *L);

#endif __LUA__FUNCTIONS__H__
