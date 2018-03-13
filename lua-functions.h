#ifndef __LUA__FUNCTIONS__H__
#define __LUA__FUNCTIONS__H__

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

void installFunctions(lua_State *L);
void installAutoexec(lua_State *L);

int ListDirectory(lua_State *L);
int ListDirectoryFiles(lua_State *L);
int ListDirectoryDirs(lua_State *L);

int Messagebox(lua_State *L);

int SdlTest(lua_State *L);

#endif __LUA__FUNCTIONS__H__
