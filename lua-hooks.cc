#include <windows.h>

#include "lua5.1.h"
#include "utils.h"
#include "lua-functions.h"


HOOK_LUA(luaL_newstate, lua_State *, ()) {
	lua_State *l = (*dll_luaL_newstate)();
	
	installFunctions(l);

	return l;
}

HOOK_LUA(lua_pcall, int, (lua_State *L, int nargs, int nresults, int errfunc)) {
	int res = (*dll_lua_pcall)(L, nargs, nresults, errfunc);
	
	if(res!=0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}

HOOK_LUA(lua_load, int, (lua_State *L, lua_Reader reader, void *dt, const char *chunkname)) {
	int res = (*dll_lua_load)(L, reader, dt, chunkname);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}
HOOK_LUA(luaL_loadbuffer, int, (lua_State *L, const char *buff, size_t sz, const char *name)) {
	int res = (*dll_luaL_loadbuffer)(L, buff, sz, name);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}
HOOK_LUA(luaL_loadstring, int, (lua_State *L, const char *s)) { 
	int res = (*dll_luaL_loadstring)(L, s);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}
HOOK_LUA(luaL_loadfile, int, (lua_State *L, const char *filename)) {
	int res = (*dll_luaL_loadfile)(L, filename);

	if(res != 0)
		error("%s\n", lua_tostring(L, -1));

	return res;
}


HOOK_LUA(lua_gettop, int, (lua_State *L)) { return (*dll_lua_gettop)(L); }
HOOK_LUA(lua_settop, void, (lua_State *L, int idx)) { return (*dll_lua_settop)(L, idx); }
HOOK_LUA(lua_pushvalue, void, (lua_State *L, int idx)) { return (*dll_lua_pushvalue)(L, idx); }
HOOK_LUA(lua_remove, void, (lua_State *L, int idx)) { return (*dll_lua_remove)(L, idx); }
HOOK_LUA(lua_insert, void, (lua_State *L, int idx)) { return (*dll_lua_insert)(L, idx); }
HOOK_LUA(lua_replace, void, (lua_State *L, int idx)) { return (*dll_lua_replace)(L, idx); }
HOOK_LUA(lua_checkstack, int, (lua_State *L, int sz)) { return (*dll_lua_checkstack)(L, sz); }
HOOK_LUA(lua_xmove, void, (lua_State *from, lua_State *to, int n)) { return (*dll_lua_xmove)(from, to, n); }
HOOK_LUA(lua_isnumber, int, (lua_State *L, int idx)) { return (*dll_lua_isnumber)(L, idx); }
HOOK_LUA(lua_isstring, int, (lua_State *L, int idx)) { return (*dll_lua_isstring)(L, idx); }
HOOK_LUA(lua_iscfunction, int, (lua_State *L, int idx)) { return (*dll_lua_iscfunction)(L, idx); }
HOOK_LUA(lua_isuserdata, int, (lua_State *L, int idx)) { return (*dll_lua_isuserdata)(L, idx); }
HOOK_LUA(lua_type, int, (lua_State *L, int idx)) { return (*dll_lua_type)(L, idx); }
HOOK_LUA(lua_typename, const char *, (lua_State *L, int tp)) { return (*dll_lua_typename)(L, tp); }
HOOK_LUA(lua_equal, int, (lua_State *L, int idx1, int idx2)) { return (*dll_lua_equal)(L, idx1, idx2); }
HOOK_LUA(lua_rawequal, int, (lua_State *L, int idx1, int idx2)) { return (*dll_lua_rawequal)(L, idx1, idx2); }
HOOK_LUA(lua_lessthan, int, (lua_State *L, int idx1, int idx2)) { return (*dll_lua_lessthan)(L, idx1, idx2); }
HOOK_LUA(lua_tonumber, lua_Number, (lua_State *L, int idx)) { return (*dll_lua_tonumber)(L, idx); }
HOOK_LUA(lua_tointeger, lua_Integer, (lua_State *L, int idx)) { return (*dll_lua_tointeger)(L, idx); }
HOOK_LUA(lua_toboolean, int, (lua_State *L, int idx)) { return (*dll_lua_toboolean)(L, idx); }
HOOK_LUA(lua_tolstring, const char *, (lua_State *L, int idx, size_t *len)) { return (*dll_lua_tolstring)(L, idx, len); }
HOOK_LUA(lua_objlen, size_t, (lua_State *L, int idx)) { return (*dll_lua_objlen)(L, idx); }
HOOK_LUA(lua_tocfunction, lua_CFunction, (lua_State *L, int idx)) { return (*dll_lua_tocfunction)(L, idx); }
HOOK_LUA(lua_touserdata, void *, (lua_State *L, int idx)) { return (*dll_lua_touserdata)(L, idx); }
HOOK_LUA(lua_tothread, lua_State *, (lua_State *L, int idx)) { return (*dll_lua_tothread)(L, idx); }
HOOK_LUA(lua_topointer, const void *, (lua_State *L, int idx)) { return (*dll_lua_topointer)(L, idx); }
HOOK_LUA(lua_pushnil, void, (lua_State *L)) { return (*dll_lua_pushnil)(L); }
HOOK_LUA(lua_pushnumber, void, (lua_State *L, lua_Number n)) { return (*dll_lua_pushnumber)(L, n); }
HOOK_LUA(lua_pushinteger, void, (lua_State *L, lua_Integer n)) { return (*dll_lua_pushinteger)(L, n); }
HOOK_LUA(lua_pushlstring, void, (lua_State *L, const char *s, size_t l)) { return (*dll_lua_pushlstring)(L, s, l); }
HOOK_LUA(lua_pushstring, void, (lua_State *L, const char *s)) { return (*dll_lua_pushstring)(L, s); }
HOOK_LUA(lua_pushvfstring, const char *, (lua_State *L, const char *fmt, va_list argp)) { return (*dll_lua_pushvfstring)(L, fmt, argp); }
HOOK_LUA(lua_pushcclosure, void, (lua_State *L, lua_CFunction fn, int n)) { return (*dll_lua_pushcclosure)(L, fn, n); }
HOOK_LUA(lua_pushboolean, void, (lua_State *L, int b)) { return (*dll_lua_pushboolean)(L, b); }
HOOK_LUA(lua_pushlightuserdata, void, (lua_State *L, void *p)) { return (*dll_lua_pushlightuserdata)(L, p); }
HOOK_LUA(lua_pushthread, int, (lua_State *L)) { return (*dll_lua_pushthread)(L); }
HOOK_LUA(lua_gettable, void, (lua_State *L, int idx)) { return (*dll_lua_gettable)(L, idx); }
HOOK_LUA(lua_getfield, void, (lua_State *L, int idx, const char *k)) { return (*dll_lua_getfield)(L, idx, k); }
HOOK_LUA(lua_rawget, void, (lua_State *L, int idx)) { return (*dll_lua_rawget)(L, idx); }
HOOK_LUA(lua_rawgeti, void, (lua_State *L, int idx, int n)) { return (*dll_lua_rawgeti)(L, idx, n); }
HOOK_LUA(lua_createtable, void, (lua_State *L, int narr, int nrec)) { return (*dll_lua_createtable)(L, narr, nrec); }
HOOK_LUA(lua_newuserdata, void *, (lua_State *L, size_t sz)) { return (*dll_lua_newuserdata)(L, sz); }
HOOK_LUA(lua_getmetatable, int, (lua_State *L, int objindex)) { return (*dll_lua_getmetatable)(L, objindex); }
HOOK_LUA(lua_getfenv, void, (lua_State *L, int idx)) { return (*dll_lua_getfenv)(L, idx); }
HOOK_LUA(lua_settable, void, (lua_State *L, int idx)) { return (*dll_lua_settable)(L, idx); }
HOOK_LUA(lua_setfield, void, (lua_State *L, int idx, const char *k)) { return (*dll_lua_setfield)(L, idx, k); }
HOOK_LUA(lua_rawset, void, (lua_State *L, int idx)) { return (*dll_lua_rawset)(L, idx); }
HOOK_LUA(lua_rawseti, void, (lua_State *L, int idx, int n)) { return (*dll_lua_rawseti)(L, idx, n); }
HOOK_LUA(lua_setmetatable, int, (lua_State *L, int objindex)) { return (*dll_lua_setmetatable)(L, objindex); }
HOOK_LUA(lua_setfenv, int, (lua_State *L, int idx)) { return (*dll_lua_setfenv)(L, idx); }
HOOK_LUA(lua_call, void, (lua_State *L, int nargs, int nresults)) { return (*dll_lua_call)(L, nargs, nresults); }
HOOK_LUA(lua_cpcall, int, (lua_State *L, lua_CFunction func, void *ud)) { return (*dll_lua_cpcall)(L, func, ud); }
HOOK_LUA(lua_dump, int, (lua_State *L, lua_Writer writer, void *data)) { return (*dll_lua_dump)(L, writer, data); }
HOOK_LUA(lua_newstate, lua_State *, (lua_Alloc f, void *ud)) { return (*dll_lua_newstate)(f, ud); }
HOOK_LUA(lua_close, void, (lua_State *L)) { return (*dll_lua_close)(L); }
HOOK_LUA(lua_newthread, lua_State *, (lua_State *L)) { return (*dll_lua_newthread)(L); }
HOOK_LUA(lua_atpanic, lua_CFunction, (lua_State *L, lua_CFunction panicf)) { return (*dll_lua_atpanic)(L, panicf); }
HOOK_LUA(lua_yield, int, (lua_State *L, int nresults)) { return (*dll_lua_yield)(L, nresults); }
HOOK_LUA(lua_resume, int, (lua_State *L, int narg)) { return (*dll_lua_resume)(L, narg); }
HOOK_LUA(lua_status, int, (lua_State *L)) { return (*dll_lua_status)(L); }
HOOK_LUA(lua_error, int, (lua_State *L)) { return (*dll_lua_error)(L); }
HOOK_LUA(luaL_openlib, void, (lua_State *L, const char *libname, const luaL_Reg *l, int nup)) { return (*dll_luaL_openlib)(L, libname, l, nup); }
HOOK_LUA(luaL_register, void, (lua_State *L, const char *libname, const luaL_Reg *l)) { return (*dll_luaL_register)(L, libname, l); }
HOOK_LUA(luaL_getmetafield, int, (lua_State *L, int obj, const char *e)) { return (*dll_luaL_getmetafield)(L, obj, e); }
HOOK_LUA(luaL_callmeta, int, (lua_State *L, int obj, const char *e)) { return (*dll_luaL_callmeta)(L, obj, e); }
HOOK_LUA(luaL_typerror, int, (lua_State *L, int narg, const char *tname)) { return (*dll_luaL_typerror)(L, narg, tname); }
HOOK_LUA(luaL_argerror, int, (lua_State *L, int numarg, const char *extramsg)) { return (*dll_luaL_argerror)(L, numarg, extramsg); }
HOOK_LUA(luaL_checklstring, const char *, (lua_State *L, int numArg, size_t *l)) { return (*dll_luaL_checklstring)(L, numArg, l); }
HOOK_LUA(luaL_optlstring, const char *, (lua_State *L, int numArg, const char *def, size_t *l)) { return (*dll_luaL_optlstring)(L, numArg, def, l); }
HOOK_LUA(luaL_checknumber, lua_Number, (lua_State *L, int numArg)) { return (*dll_luaL_checknumber)(L, numArg); }
HOOK_LUA(luaL_optnumber, lua_Number, (lua_State *L, int nArg, lua_Number def)) { return (*dll_luaL_optnumber)(L, nArg, def); }
HOOK_LUA(luaL_checkinteger, lua_Integer, (lua_State *L, int numArg)) { return (*dll_luaL_checkinteger)(L, numArg); }
HOOK_LUA(luaL_optinteger, lua_Integer, (lua_State *L, int nArg, lua_Integer def)) { return (*dll_luaL_optinteger)(L, nArg, def); }
HOOK_LUA(luaL_checkstack, void, (lua_State *L, int sz, const char *msg)) { return (*dll_luaL_checkstack)(L, sz, msg); }
HOOK_LUA(luaL_checktype, void, (lua_State *L, int narg, int t)) { return (*dll_luaL_checktype)(L, narg, t); }
HOOK_LUA(luaL_checkany, void, (lua_State *L, int narg)) { return (*dll_luaL_checkany)(L, narg); }
HOOK_LUA(luaL_newmetatable, int, (lua_State *L, const char *tname)) { return (*dll_luaL_newmetatable)(L, tname); }
HOOK_LUA(luaL_checkudata, void *, (lua_State *L, int ud, const char *tname)) { return (*dll_luaL_checkudata)(L, ud, tname); }
HOOK_LUA(luaL_where, void, (lua_State *L, int lvl)) { return (*dll_luaL_where)(L, lvl); }
HOOK_LUA(luaL_checkoption, int, (lua_State *L, int narg, const char *def, const char *const lst[])) { return (*dll_luaL_checkoption)(L, narg, def, lst); }
HOOK_LUA(luaL_ref, int, (lua_State *L, int t)) { return (*dll_luaL_ref)(L, t); }
HOOK_LUA(luaL_unref, void, (lua_State *L, int t, int ref)) { return (*dll_luaL_unref)(L, t, ref); }
HOOK_LUA(luaL_gsub, const char *, (lua_State *L, const char *s, const char *p, const char *r)) { return (*dll_luaL_gsub)(L, s, p, r); }
HOOK_LUA(luaL_findtable, const char *, (lua_State *L, int idx, const char *fname, int szhint)) { return (*dll_luaL_findtable)(L, idx, fname, szhint); }

HOOK_LUA(luaL_openlibs, void, (lua_State *L)) { return (*dll_luaL_openlibs)(L); }


HOOK_LUA(lua_pushfstring, const char *, (lua_State *L, const char *fmt, ...)) {
	va_list ap;
	va_start(ap, fmt);
	const char *res = (*dll_lua_pushvfstring)(L, fmt, ap);
	va_end(ap);
	return res;
}

HOOK_LUA(luaL_error, int, (lua_State *L, const char *fmt, ...)) {
	va_list ap;
	va_start(ap, fmt);
	std::string text = formatv(fmt, ap);
	va_end(ap);

	return (*dll_luaL_error)(L, "%s", text.c_str());
}
