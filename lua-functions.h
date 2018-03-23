#ifndef __LUA__FUNCTIONS__H__
#define __LUA__FUNCTIONS__H__

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

void installFunctions(lua_State *L);
void installAutoexec(lua_State *L);

#endif __LUA__FUNCTIONS__H__
