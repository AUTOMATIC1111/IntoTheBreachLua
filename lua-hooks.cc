#include <windows.h>

#include "lua5.1.h"
#include "utils.h"
#include "lua-functions.h"


HOOK(luaL_newstate, lua_State *, ()) {
	lua_State *l = (*dll_luaL_newstate)();

	installFunctions(l);

	lua_pushcfunction(l, Messagebox);
	lua_setglobal(l, "messagebox");

	lua_pushcfunction(l, ListDirectory);
	lua_setglobal(l, "listall");

	lua_pushcfunction(l, ListDirectoryFiles);
	lua_setglobal(l, "listfiles");

	lua_pushcfunction(l, ListDirectoryDirs);
	lua_setglobal(l, "listdirs");

	lua_pushcfunction(l, SdlTest);
	lua_setglobal(l, "sdltest");

	return l;
}

HOOK(lua_pcall, int, (lua_State *L, int nargs, int nresults, int errfunc)) {
	int res = (*dll_lua_pcall)(L, nargs, nresults, errfunc);
	
	if(res!=0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}

HOOK(lua_load, int, (lua_State *L, lua_Reader reader, void *dt, const char *chunkname)) {
	int res = (*dll_lua_load)(L, reader, dt, chunkname);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}
HOOK(luaL_loadbuffer, int, (lua_State *L, const char *buff, size_t sz, const char *name)) {
	int res = (*dll_luaL_loadbuffer)(L, buff, sz, name);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}
HOOK(luaL_loadstring, int, (lua_State *L, const char *s)) { 
	int res = (*dll_luaL_loadstring)(L, s);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}


HOOK(luaL_loadfile, int, (lua_State *L, const char *filename)) {
//	if(strcmp(filename, "scripts/items.lua") == 0)
//		installAutoexec(L);
	
	int res = (*dll_luaL_loadfile)(L, filename);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}


HOOK(lua_gettop, int, (lua_State *L)) { return (*dll_lua_gettop)(L); }
HOOK(lua_settop, void, (lua_State *L, int idx)) { return (*dll_lua_settop)(L, idx); }
HOOK(lua_pushvalue, void, (lua_State *L, int idx)) { return (*dll_lua_pushvalue)(L, idx); }
HOOK(lua_remove, void, (lua_State *L, int idx)) { return (*dll_lua_remove)(L, idx); }
HOOK(lua_insert, void, (lua_State *L, int idx)) { return (*dll_lua_insert)(L, idx); }
HOOK(lua_replace, void, (lua_State *L, int idx)) { return (*dll_lua_replace)(L, idx); }
HOOK(lua_checkstack, int, (lua_State *L, int sz)) { return (*dll_lua_checkstack)(L, sz); }
HOOK(lua_xmove, void, (lua_State *from, lua_State *to, int n)) { return (*dll_lua_xmove)(from, to, n); }
HOOK(lua_isnumber, int, (lua_State *L, int idx)) { return (*dll_lua_isnumber)(L, idx); }
HOOK(lua_isstring, int, (lua_State *L, int idx)) { return (*dll_lua_isstring)(L, idx); }
HOOK(lua_iscfunction, int, (lua_State *L, int idx)) { return (*dll_lua_iscfunction)(L, idx); }
HOOK(lua_isuserdata, int, (lua_State *L, int idx)) { return (*dll_lua_isuserdata)(L, idx); }
HOOK(lua_type, int, (lua_State *L, int idx)) { return (*dll_lua_type)(L, idx); }
HOOK(lua_typename, const char *, (lua_State *L, int tp)) { return (*dll_lua_typename)(L, tp); }
HOOK(lua_equal, int, (lua_State *L, int idx1, int idx2)) { return (*dll_lua_equal)(L, idx1, idx2); }
HOOK(lua_rawequal, int, (lua_State *L, int idx1, int idx2)) { return (*dll_lua_rawequal)(L, idx1, idx2); }
HOOK(lua_lessthan, int, (lua_State *L, int idx1, int idx2)) { return (*dll_lua_lessthan)(L, idx1, idx2); }
HOOK(lua_tonumber, lua_Number, (lua_State *L, int idx)) { return (*dll_lua_tonumber)(L, idx); }
HOOK(lua_tointeger, lua_Integer, (lua_State *L, int idx)) { return (*dll_lua_tointeger)(L, idx); }
HOOK(lua_toboolean, int, (lua_State *L, int idx)) { return (*dll_lua_toboolean)(L, idx); }
HOOK(lua_tolstring, const char *, (lua_State *L, int idx, size_t *len)) { return (*dll_lua_tolstring)(L, idx, len); }
HOOK(lua_objlen, size_t, (lua_State *L, int idx)) { return (*dll_lua_objlen)(L, idx); }
HOOK(lua_tocfunction, lua_CFunction, (lua_State *L, int idx)) { return (*dll_lua_tocfunction)(L, idx); }
HOOK(lua_touserdata, void *, (lua_State *L, int idx)) { return (*dll_lua_touserdata)(L, idx); }
HOOK(lua_tothread, lua_State *, (lua_State *L, int idx)) { return (*dll_lua_tothread)(L, idx); }
HOOK(lua_topointer, const void *, (lua_State *L, int idx)) { return (*dll_lua_topointer)(L, idx); }
HOOK(lua_pushnil, void, (lua_State *L)) { return (*dll_lua_pushnil)(L); }
HOOK(lua_pushnumber, void, (lua_State *L, lua_Number n)) { return (*dll_lua_pushnumber)(L, n); }
HOOK(lua_pushinteger, void, (lua_State *L, lua_Integer n)) { return (*dll_lua_pushinteger)(L, n); }
HOOK(lua_pushlstring, void, (lua_State *L, const char *s, size_t l)) { return (*dll_lua_pushlstring)(L, s, l); }
HOOK(lua_pushstring, void, (lua_State *L, const char *s)) { return (*dll_lua_pushstring)(L, s); }
HOOK(lua_pushvfstring, const char *, (lua_State *L, const char *fmt, va_list argp)) { return (*dll_lua_pushvfstring)(L, fmt, argp); }
HOOK(lua_pushcclosure, void, (lua_State *L, lua_CFunction fn, int n)) { return (*dll_lua_pushcclosure)(L, fn, n); }
HOOK(lua_pushboolean, void, (lua_State *L, int b)) { return (*dll_lua_pushboolean)(L, b); }
HOOK(lua_pushlightuserdata, void, (lua_State *L, void *p)) { return (*dll_lua_pushlightuserdata)(L, p); }
HOOK(lua_pushthread, int, (lua_State *L)) { return (*dll_lua_pushthread)(L); }
HOOK(lua_gettable, void, (lua_State *L, int idx)) { return (*dll_lua_gettable)(L, idx); }
HOOK(lua_getfield, void, (lua_State *L, int idx, const char *k)) { return (*dll_lua_getfield)(L, idx, k); }
HOOK(lua_rawget, void, (lua_State *L, int idx)) { return (*dll_lua_rawget)(L, idx); }
HOOK(lua_rawgeti, void, (lua_State *L, int idx, int n)) { return (*dll_lua_rawgeti)(L, idx, n); }
HOOK(lua_createtable, void, (lua_State *L, int narr, int nrec)) { return (*dll_lua_createtable)(L, narr, nrec); }
HOOK(lua_newuserdata, void *, (lua_State *L, size_t sz)) { return (*dll_lua_newuserdata)(L, sz); }
HOOK(lua_getmetatable, int, (lua_State *L, int objindex)) { return (*dll_lua_getmetatable)(L, objindex); }
HOOK(lua_getfenv, void, (lua_State *L, int idx)) { return (*dll_lua_getfenv)(L, idx); }
HOOK(lua_settable, void, (lua_State *L, int idx)) { return (*dll_lua_settable)(L, idx); }
HOOK(lua_setfield, void, (lua_State *L, int idx, const char *k)) { return (*dll_lua_setfield)(L, idx, k); }
HOOK(lua_rawset, void, (lua_State *L, int idx)) { return (*dll_lua_rawset)(L, idx); }
HOOK(lua_rawseti, void, (lua_State *L, int idx, int n)) { return (*dll_lua_rawseti)(L, idx, n); }
HOOK(lua_setmetatable, int, (lua_State *L, int objindex)) { return (*dll_lua_setmetatable)(L, objindex); }
HOOK(lua_setfenv, int, (lua_State *L, int idx)) { return (*dll_lua_setfenv)(L, idx); }
HOOK(lua_call, void, (lua_State *L, int nargs, int nresults)) { return (*dll_lua_call)(L, nargs, nresults); }
HOOK(lua_cpcall, int, (lua_State *L, lua_CFunction func, void *ud)) { return (*dll_lua_cpcall)(L, func, ud); }
HOOK(lua_dump, int, (lua_State *L, lua_Writer writer, void *data)) { return (*dll_lua_dump)(L, writer, data); }
HOOK(lua_newstate, lua_State *, (lua_Alloc f, void *ud)) { return (*dll_lua_newstate)(f, ud); }
HOOK(lua_close, void, (lua_State *L)) { return (*dll_lua_close)(L); }
HOOK(lua_newthread, lua_State *, (lua_State *L)) { return (*dll_lua_newthread)(L); }
HOOK(lua_atpanic, lua_CFunction, (lua_State *L, lua_CFunction panicf)) { return (*dll_lua_atpanic)(L, panicf); }
HOOK(lua_yield, int, (lua_State *L, int nresults)) { return (*dll_lua_yield)(L, nresults); }
HOOK(lua_resume, int, (lua_State *L, int narg)) { return (*dll_lua_resume)(L, narg); }
HOOK(lua_status, int, (lua_State *L)) { return (*dll_lua_status)(L); }
HOOK(lua_error, int, (lua_State *L)) { return (*dll_lua_error)(L); }
HOOK(luaL_openlib, void, (lua_State *L, const char *libname, const luaL_Reg *l, int nup)) { return (*dll_luaL_openlib)(L, libname, l, nup); }
HOOK(luaL_register, void, (lua_State *L, const char *libname, const luaL_Reg *l)) { return (*dll_luaL_register)(L, libname, l); }
HOOK(luaL_getmetafield, int, (lua_State *L, int obj, const char *e)) { return (*dll_luaL_getmetafield)(L, obj, e); }
HOOK(luaL_callmeta, int, (lua_State *L, int obj, const char *e)) { return (*dll_luaL_callmeta)(L, obj, e); }
HOOK(luaL_typerror, int, (lua_State *L, int narg, const char *tname)) { return (*dll_luaL_typerror)(L, narg, tname); }
HOOK(luaL_argerror, int, (lua_State *L, int numarg, const char *extramsg)) { return (*dll_luaL_argerror)(L, numarg, extramsg); }
HOOK(luaL_checklstring, const char *, (lua_State *L, int numArg, size_t *l)) { return (*dll_luaL_checklstring)(L, numArg, l); }
HOOK(luaL_optlstring, const char *, (lua_State *L, int numArg, const char *def, size_t *l)) { return (*dll_luaL_optlstring)(L, numArg, def, l); }
HOOK(luaL_checknumber, lua_Number, (lua_State *L, int numArg)) { return (*dll_luaL_checknumber)(L, numArg); }
HOOK(luaL_optnumber, lua_Number, (lua_State *L, int nArg, lua_Number def)) { return (*dll_luaL_optnumber)(L, nArg, def); }
HOOK(luaL_checkinteger, lua_Integer, (lua_State *L, int numArg)) { return (*dll_luaL_checkinteger)(L, numArg); }
HOOK(luaL_optinteger, lua_Integer, (lua_State *L, int nArg, lua_Integer def)) { return (*dll_luaL_optinteger)(L, nArg, def); }
HOOK(luaL_checkstack, void, (lua_State *L, int sz, const char *msg)) { return (*dll_luaL_checkstack)(L, sz, msg); }
HOOK(luaL_checktype, void, (lua_State *L, int narg, int t)) { return (*dll_luaL_checktype)(L, narg, t); }
HOOK(luaL_checkany, void, (lua_State *L, int narg)) { return (*dll_luaL_checkany)(L, narg); }
HOOK(luaL_newmetatable, int, (lua_State *L, const char *tname)) { return (*dll_luaL_newmetatable)(L, tname); }
HOOK(luaL_checkudata, void *, (lua_State *L, int ud, const char *tname)) { return (*dll_luaL_checkudata)(L, ud, tname); }
HOOK(luaL_where, void, (lua_State *L, int lvl)) { return (*dll_luaL_where)(L, lvl); }
HOOK(luaL_checkoption, int, (lua_State *L, int narg, const char *def, const char *const lst[])) { return (*dll_luaL_checkoption)(L, narg, def, lst); }
HOOK(luaL_ref, int, (lua_State *L, int t)) { return (*dll_luaL_ref)(L, t); }
HOOK(luaL_unref, void, (lua_State *L, int t, int ref)) { return (*dll_luaL_unref)(L, t, ref); }
HOOK(luaL_gsub, const char *, (lua_State *L, const char *s, const char *p, const char *r)) { return (*dll_luaL_gsub)(L, s, p, r); }
HOOK(luaL_findtable, const char *, (lua_State *L, int idx, const char *fname, int szhint)) { return (*dll_luaL_findtable)(L, idx, fname, szhint); }

HOOK(luaL_openlibs, void, (lua_State *L)) { return (*dll_luaL_openlibs)(L); }


HOOK(lua_pushfstring, const char *, (lua_State *L, const char *fmt, ...)) {
	va_list ap;
	va_start(ap, fmt);
	const char *res = (*dll_lua_pushvfstring)(L, fmt, ap);
	va_end(ap);
	return res;
}

HOOK(luaL_error, int, (lua_State *L, const char *fmt, ...)) {
	va_list ap;
	va_start(ap, fmt);
	std::string text = formatv(fmt, ap);
	va_end(ap);

	return (*dll_luaL_error)(L, "%s", text.c_str());
}
