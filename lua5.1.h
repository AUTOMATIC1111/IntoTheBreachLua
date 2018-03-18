#ifndef __LUA__5_1_h__
#define __LUA__5_1_h__

#include <windows.h>
#include "lua.h"
#include "lauxlib.h"


#define HOOK_LUA(name,rettype,args) \
static rettype (**dll_##name) args = (rettype (**) args) (void *) &luaTable[ LUA_N_##name ]; \
extern "C" __declspec(dllexport) rettype name args

extern FARPROC luaTable[];

#define HOOK_GENERIC(dllname,name,rettype,args) \
struct dll_loader_t_##name{ \
	HINSTANCE lib; \
	FARPROC func; \
	dll_loader_t_##name(){ lib = LoadLibraryA(dllname); func = GetProcAddress(lib, #name); } \
	~dll_loader_t_##name(){ if(lib) FreeLibrary(lib); } \
}; \
static dll_loader_t_##name dll_loader_##name; \
static rettype (**dll_##name) args = (rettype (**) args) (void *) dll_loader_##name.func; \
extern "C" __declspec(dllexport) rettype name args

#define LUA_N_luaL_addlstring 0
#define LUA_N_luaL_addstring 1
#define LUA_N_luaL_addvalue 2
#define LUA_N_luaL_argerror 3
#define LUA_N_luaL_buffinit 4
#define LUA_N_luaL_callmeta 5
#define LUA_N_luaL_checkany 6
#define LUA_N_luaL_checkinteger 7
#define LUA_N_luaL_checklstring 8
#define LUA_N_luaL_checknumber 9
#define LUA_N_luaL_checkoption 10
#define LUA_N_luaL_checkstack 11
#define LUA_N_luaL_checktype 12
#define LUA_N_luaL_checkudata 13
#define LUA_N_luaL_error 14
#define LUA_N_luaL_findtable 15
#define LUA_N_luaL_getmetafield 16
#define LUA_N_luaL_gsub 17
#define LUA_N_luaL_loadbuffer 18
#define LUA_N_luaL_loadfile 19
#define LUA_N_luaL_loadstring 20
#define LUA_N_luaL_newmetatable 21
#define LUA_N_luaL_newstate 22
#define LUA_N_luaL_openlib 23
#define LUA_N_luaL_openlibs 24
#define LUA_N_luaL_optinteger 25
#define LUA_N_luaL_optlstring 26
#define LUA_N_luaL_optnumber 27
#define LUA_N_luaL_prepbuffer 28
#define LUA_N_luaL_pushresult 29
#define LUA_N_luaL_ref 30
#define LUA_N_luaL_register 31
#define LUA_N_luaL_typerror 32
#define LUA_N_luaL_unref 33
#define LUA_N_luaL_where 34
#define LUA_N_lua_atpanic 35
#define LUA_N_lua_call 36
#define LUA_N_lua_checkstack 37
#define LUA_N_lua_close 38
#define LUA_N_lua_concat 39
#define LUA_N_lua_cpcall 40
#define LUA_N_lua_createtable 41
#define LUA_N_lua_dump 42
#define LUA_N_lua_equal 43
#define LUA_N_lua_error 44
#define LUA_N_lua_gc 45
#define LUA_N_lua_getallocf 46
#define LUA_N_lua_getfenv 47
#define LUA_N_lua_getfield 48
#define LUA_N_lua_gethook 49
#define LUA_N_lua_gethookcount 50
#define LUA_N_lua_gethookmask 51
#define LUA_N_lua_getinfo 52
#define LUA_N_lua_getlocal 53
#define LUA_N_lua_getmetatable 54
#define LUA_N_lua_getstack 55
#define LUA_N_lua_gettable 56
#define LUA_N_lua_gettop 57
#define LUA_N_lua_getupvalue 58
#define LUA_N_lua_insert 59
#define LUA_N_lua_iscfunction 60
#define LUA_N_lua_isnumber 61
#define LUA_N_lua_isstring 62
#define LUA_N_lua_isuserdata 63
#define LUA_N_lua_lessthan 64
#define LUA_N_lua_load 65
#define LUA_N_lua_newstate 66
#define LUA_N_lua_newthread 67
#define LUA_N_lua_newuserdata 68
#define LUA_N_lua_next 69
#define LUA_N_lua_objlen 70
#define LUA_N_lua_pcall 71
#define LUA_N_lua_pushboolean 72
#define LUA_N_lua_pushcclosure 73
#define LUA_N_lua_pushfstring 74
#define LUA_N_lua_pushinteger 75
#define LUA_N_lua_pushlightuserdata 76
#define LUA_N_lua_pushlstring 77
#define LUA_N_lua_pushnil 78
#define LUA_N_lua_pushnumber 79
#define LUA_N_lua_pushstring 80
#define LUA_N_lua_pushthread 81
#define LUA_N_lua_pushvalue 82
#define LUA_N_lua_pushvfstring 83
#define LUA_N_lua_rawequal 84
#define LUA_N_lua_rawget 85
#define LUA_N_lua_rawgeti 86
#define LUA_N_lua_rawset 87
#define LUA_N_lua_rawseti 88
#define LUA_N_lua_remove 89
#define LUA_N_lua_replace 90
#define LUA_N_lua_resume 91
#define LUA_N_lua_setallocf 92
#define LUA_N_lua_setfenv 93
#define LUA_N_lua_setfield 94
#define LUA_N_lua_sethook 95
#define LUA_N_lua_setlevel 96
#define LUA_N_lua_setlocal 97
#define LUA_N_lua_setmetatable 98
#define LUA_N_lua_settable 99
#define LUA_N_lua_settop 100
#define LUA_N_lua_setupvalue 101
#define LUA_N_lua_status 102
#define LUA_N_lua_toboolean 103
#define LUA_N_lua_tocfunction 104
#define LUA_N_lua_tointeger 105
#define LUA_N_lua_tolstring 106
#define LUA_N_lua_tonumber 107
#define LUA_N_lua_topointer 108
#define LUA_N_lua_tothread 109
#define LUA_N_lua_touserdata 110
#define LUA_N_lua_type 111
#define LUA_N_lua_typename 112
#define LUA_N_lua_xmove 113
#define LUA_N_lua_yield 114
#define LUA_N_luaopen_base 115
#define LUA_N_luaopen_debug 116
#define LUA_N_luaopen_io 117
#define LUA_N_luaopen_math 118
#define LUA_N_luaopen_os 119
#define LUA_N_luaopen_package 120
#define LUA_N_luaopen_string 121
#define LUA_N_luaopen_table 122

#endif
