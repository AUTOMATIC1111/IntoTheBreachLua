#include <windows.h>

#include "lua5.1.h"
#include "utils.h"
#include "lua-functions.h"

HOOK(luaL_newstate, lua_State *, ()) {
	lua_State *l = (*dll_luaL_newstate)();

	lua_pushcfunction(l, Messagebox);
	lua_setglobal(l, "messagebox");

	lua_pushcfunction(l, ListDirectory);
	lua_setglobal(l, "listall");

	lua_pushcfunction(l, ListDirectoryFiles);
	lua_setglobal(l, "listfiles");

	lua_pushcfunction(l, ListDirectoryDirs);
	lua_setglobal(l, "listdirs");

	return l;
}

HOOK(lua_call, void, (lua_State *L, int nargs, int nresults)) {
	return (*dll_lua_call)(L, nargs, nresults);
}

HOOK(lua_pushcclosure, void, (lua_State *L, lua_CFunction fn, int n)) {
	return (*dll_lua_pushcclosure)(L, fn, n);
}

HOOK(lua_setfield, void, (lua_State *L, int idx, const char *k)) {
	return (*dll_lua_setfield)(L, idx, k);
}

HOOK(lua_createtable, void, (lua_State *L, int narr, int nrec)) {
	return (*dll_lua_createtable)(L, narr, nrec);
}

HOOK(lua_pushnumber, void, (lua_State *L, lua_Number n)) {
	return (*dll_lua_pushnumber)(L, n);
}

HOOK(lua_pushstring, void, (lua_State *L, const char *s)) {
	return (*dll_lua_pushstring)(L, s);
}

HOOK(lua_settable, void, (lua_State *L, int idx)) {
	return (*dll_lua_settable)(L, idx);
}

HOOK(lua_tolstring, const char *, (lua_State *L, int idx, size_t *len)) {
	return (*dll_lua_tolstring)(L, idx, len);
}
