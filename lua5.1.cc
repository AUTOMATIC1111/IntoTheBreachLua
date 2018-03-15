#include <windows.h>
#include "hook.h"
#include <SDL.h>
#include <stdio.h>
#pragma pack(1)


static HINSTANCE libHandle = 0;
FARPROC luaTable[123] = { 0 };

extern void __cdecl MySDL_GL_SwapWindow(SDL_Window * window) {
	printf("oops!\n");
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
	if(reason == DLL_PROCESS_DETACH) {
		FreeLibrary(libHandle);
	}

	if(reason != DLL_PROCESS_ATTACH) {
		return 1;
	}

	libHandle = LoadLibraryA("lua5.1-original.dll");
	if(!libHandle) return false;

	/*
	HINSTANCE libHandle = LoadLibraryA("SDL2.dll");
	if(!libHandle) return false;
	FARPROC func = GetProcAddress(libHandle, "SDL_GL_SwapWindow");
	hookSweep((int) func, MySDL_GL_SwapWindow, NULL);
	*/

	luaTable[0] = GetProcAddress(libHandle, "luaL_addlstring");
	luaTable[1] = GetProcAddress(libHandle, "luaL_addstring");
	luaTable[2] = GetProcAddress(libHandle, "luaL_addvalue");
	luaTable[3] = GetProcAddress(libHandle, "luaL_argerror");
	luaTable[4] = GetProcAddress(libHandle, "luaL_buffinit");
	luaTable[5] = GetProcAddress(libHandle, "luaL_callmeta");
	luaTable[6] = GetProcAddress(libHandle, "luaL_checkany");
	luaTable[7] = GetProcAddress(libHandle, "luaL_checkinteger");
	luaTable[8] = GetProcAddress(libHandle, "luaL_checklstring");
	luaTable[9] = GetProcAddress(libHandle, "luaL_checknumber");
	luaTable[10] = GetProcAddress(libHandle, "luaL_checkoption");
	luaTable[11] = GetProcAddress(libHandle, "luaL_checkstack");
	luaTable[12] = GetProcAddress(libHandle, "luaL_checktype");
	luaTable[13] = GetProcAddress(libHandle, "luaL_checkudata");
	luaTable[14] = GetProcAddress(libHandle, "luaL_error");
	luaTable[15] = GetProcAddress(libHandle, "luaL_findtable");
	luaTable[16] = GetProcAddress(libHandle, "luaL_getmetafield");
	luaTable[17] = GetProcAddress(libHandle, "luaL_gsub");
	luaTable[18] = GetProcAddress(libHandle, "luaL_loadbuffer");
	luaTable[19] = GetProcAddress(libHandle, "luaL_loadfile");
	luaTable[20] = GetProcAddress(libHandle, "luaL_loadstring");
	luaTable[21] = GetProcAddress(libHandle, "luaL_newmetatable");
	luaTable[22] = GetProcAddress(libHandle, "luaL_newstate");
	luaTable[23] = GetProcAddress(libHandle, "luaL_openlib");
	luaTable[24] = GetProcAddress(libHandle, "luaL_openlibs");
	luaTable[25] = GetProcAddress(libHandle, "luaL_optinteger");
	luaTable[26] = GetProcAddress(libHandle, "luaL_optlstring");
	luaTable[27] = GetProcAddress(libHandle, "luaL_optnumber");
	luaTable[28] = GetProcAddress(libHandle, "luaL_prepbuffer");
	luaTable[29] = GetProcAddress(libHandle, "luaL_pushresult");
	luaTable[30] = GetProcAddress(libHandle, "luaL_ref");
	luaTable[31] = GetProcAddress(libHandle, "luaL_register");
	luaTable[32] = GetProcAddress(libHandle, "luaL_typerror");
	luaTable[33] = GetProcAddress(libHandle, "luaL_unref");
	luaTable[34] = GetProcAddress(libHandle, "luaL_where");
	luaTable[35] = GetProcAddress(libHandle, "lua_atpanic");
	luaTable[36] = GetProcAddress(libHandle, "lua_call");
	luaTable[37] = GetProcAddress(libHandle, "lua_checkstack");
	luaTable[38] = GetProcAddress(libHandle, "lua_close");
	luaTable[39] = GetProcAddress(libHandle, "lua_concat");
	luaTable[40] = GetProcAddress(libHandle, "lua_cpcall");
	luaTable[41] = GetProcAddress(libHandle, "lua_createtable");
	luaTable[42] = GetProcAddress(libHandle, "lua_dump");
	luaTable[43] = GetProcAddress(libHandle, "lua_equal");
	luaTable[44] = GetProcAddress(libHandle, "lua_error");
	luaTable[45] = GetProcAddress(libHandle, "lua_gc");
	luaTable[46] = GetProcAddress(libHandle, "lua_getallocf");
	luaTable[47] = GetProcAddress(libHandle, "lua_getfenv");
	luaTable[48] = GetProcAddress(libHandle, "lua_getfield");
	luaTable[49] = GetProcAddress(libHandle, "lua_gethook");
	luaTable[50] = GetProcAddress(libHandle, "lua_gethookcount");
	luaTable[51] = GetProcAddress(libHandle, "lua_gethookmask");
	luaTable[52] = GetProcAddress(libHandle, "lua_getinfo");
	luaTable[53] = GetProcAddress(libHandle, "lua_getlocal");
	luaTable[54] = GetProcAddress(libHandle, "lua_getmetatable");
	luaTable[55] = GetProcAddress(libHandle, "lua_getstack");
	luaTable[56] = GetProcAddress(libHandle, "lua_gettable");
	luaTable[57] = GetProcAddress(libHandle, "lua_gettop");
	luaTable[58] = GetProcAddress(libHandle, "lua_getupvalue");
	luaTable[59] = GetProcAddress(libHandle, "lua_insert");
	luaTable[60] = GetProcAddress(libHandle, "lua_iscfunction");
	luaTable[61] = GetProcAddress(libHandle, "lua_isnumber");
	luaTable[62] = GetProcAddress(libHandle, "lua_isstring");
	luaTable[63] = GetProcAddress(libHandle, "lua_isuserdata");
	luaTable[64] = GetProcAddress(libHandle, "lua_lessthan");
	luaTable[65] = GetProcAddress(libHandle, "lua_load");
	luaTable[66] = GetProcAddress(libHandle, "lua_newstate");
	luaTable[67] = GetProcAddress(libHandle, "lua_newthread");
	luaTable[68] = GetProcAddress(libHandle, "lua_newuserdata");
	luaTable[69] = GetProcAddress(libHandle, "lua_next");
	luaTable[70] = GetProcAddress(libHandle, "lua_objlen");
	luaTable[71] = GetProcAddress(libHandle, "lua_pcall");
	luaTable[72] = GetProcAddress(libHandle, "lua_pushboolean");
	luaTable[73] = GetProcAddress(libHandle, "lua_pushcclosure");
	luaTable[74] = GetProcAddress(libHandle, "lua_pushfstring");
	luaTable[75] = GetProcAddress(libHandle, "lua_pushinteger");
	luaTable[76] = GetProcAddress(libHandle, "lua_pushlightuserdata");
	luaTable[77] = GetProcAddress(libHandle, "lua_pushlstring");
	luaTable[78] = GetProcAddress(libHandle, "lua_pushnil");
	luaTable[79] = GetProcAddress(libHandle, "lua_pushnumber");
	luaTable[80] = GetProcAddress(libHandle, "lua_pushstring");
	luaTable[81] = GetProcAddress(libHandle, "lua_pushthread");
	luaTable[82] = GetProcAddress(libHandle, "lua_pushvalue");
	luaTable[83] = GetProcAddress(libHandle, "lua_pushvfstring");
	luaTable[84] = GetProcAddress(libHandle, "lua_rawequal");
	luaTable[85] = GetProcAddress(libHandle, "lua_rawget");
	luaTable[86] = GetProcAddress(libHandle, "lua_rawgeti");
	luaTable[87] = GetProcAddress(libHandle, "lua_rawset");
	luaTable[88] = GetProcAddress(libHandle, "lua_rawseti");
	luaTable[89] = GetProcAddress(libHandle, "lua_remove");
	luaTable[90] = GetProcAddress(libHandle, "lua_replace");
	luaTable[91] = GetProcAddress(libHandle, "lua_resume");
	luaTable[92] = GetProcAddress(libHandle, "lua_setallocf");
	luaTable[93] = GetProcAddress(libHandle, "lua_setfenv");
	luaTable[94] = GetProcAddress(libHandle, "lua_setfield");
	luaTable[95] = GetProcAddress(libHandle, "lua_sethook");
	luaTable[96] = GetProcAddress(libHandle, "lua_setlevel");
	luaTable[97] = GetProcAddress(libHandle, "lua_setlocal");
	luaTable[98] = GetProcAddress(libHandle, "lua_setmetatable");
	luaTable[99] = GetProcAddress(libHandle, "lua_settable");
	luaTable[100] = GetProcAddress(libHandle, "lua_settop");
	luaTable[101] = GetProcAddress(libHandle, "lua_setupvalue");
	luaTable[102] = GetProcAddress(libHandle, "lua_status");
	luaTable[103] = GetProcAddress(libHandle, "lua_toboolean");
	luaTable[104] = GetProcAddress(libHandle, "lua_tocfunction");
	luaTable[105] = GetProcAddress(libHandle, "lua_tointeger");
	luaTable[106] = GetProcAddress(libHandle, "lua_tolstring");
	luaTable[107] = GetProcAddress(libHandle, "lua_tonumber");
	luaTable[108] = GetProcAddress(libHandle, "lua_topointer");
	luaTable[109] = GetProcAddress(libHandle, "lua_tothread");
	luaTable[110] = GetProcAddress(libHandle, "lua_touserdata");
	luaTable[111] = GetProcAddress(libHandle, "lua_type");
	luaTable[112] = GetProcAddress(libHandle, "lua_typename");
	luaTable[113] = GetProcAddress(libHandle, "lua_xmove");
	luaTable[114] = GetProcAddress(libHandle, "lua_yield");
	luaTable[115] = GetProcAddress(libHandle, "luaopen_base");
	luaTable[116] = GetProcAddress(libHandle, "luaopen_debug");
	luaTable[117] = GetProcAddress(libHandle, "luaopen_io");
	luaTable[118] = GetProcAddress(libHandle, "luaopen_math");
	luaTable[119] = GetProcAddress(libHandle, "luaopen_os");
	luaTable[120] = GetProcAddress(libHandle, "luaopen_package");
	luaTable[121] = GetProcAddress(libHandle, "luaopen_string");
	luaTable[122] = GetProcAddress(libHandle, "luaopen_table");

	return 1;
}

#define LUA_PROXY(n) extern "C" __declspec(naked) void __stdcall __E__##n##__() { { __asm jmp luaTable[n * 4] } }
LUA_PROXY(0)
LUA_PROXY(1)
LUA_PROXY(2)
LUA_PROXY(3)
LUA_PROXY(4)
LUA_PROXY(5)
LUA_PROXY(6)
LUA_PROXY(7)
LUA_PROXY(8)
LUA_PROXY(9)
LUA_PROXY(10)
LUA_PROXY(11)
LUA_PROXY(12)
LUA_PROXY(13)
LUA_PROXY(14)
LUA_PROXY(15)
LUA_PROXY(16)
LUA_PROXY(17)
LUA_PROXY(18)
LUA_PROXY(19)
LUA_PROXY(20)
LUA_PROXY(21)
LUA_PROXY(22)
LUA_PROXY(23)
LUA_PROXY(24)
LUA_PROXY(25)
LUA_PROXY(26)
LUA_PROXY(27)
LUA_PROXY(28)
LUA_PROXY(29)
LUA_PROXY(30)
LUA_PROXY(31)
LUA_PROXY(32)
LUA_PROXY(33)
LUA_PROXY(34)
LUA_PROXY(35)
LUA_PROXY(36)
LUA_PROXY(37)
LUA_PROXY(38)
LUA_PROXY(39)
LUA_PROXY(40)
LUA_PROXY(41)
LUA_PROXY(42)
LUA_PROXY(43)
LUA_PROXY(44)
LUA_PROXY(45)
LUA_PROXY(46)
LUA_PROXY(47)
LUA_PROXY(48)
LUA_PROXY(49)
LUA_PROXY(50)
LUA_PROXY(51)
LUA_PROXY(52)
LUA_PROXY(53)
LUA_PROXY(54)
LUA_PROXY(55)
LUA_PROXY(56)
LUA_PROXY(57)
LUA_PROXY(58)
LUA_PROXY(59)
LUA_PROXY(60)
LUA_PROXY(61)
LUA_PROXY(62)
LUA_PROXY(63)
LUA_PROXY(64)
LUA_PROXY(65)
LUA_PROXY(66)
LUA_PROXY(67)
LUA_PROXY(68)
LUA_PROXY(69)
LUA_PROXY(70)
LUA_PROXY(71)
LUA_PROXY(72)
LUA_PROXY(73)
LUA_PROXY(74)
LUA_PROXY(75)
LUA_PROXY(76)
LUA_PROXY(77)
LUA_PROXY(78)
LUA_PROXY(79)
LUA_PROXY(80)
LUA_PROXY(81)
LUA_PROXY(82)
LUA_PROXY(83)
LUA_PROXY(84)
LUA_PROXY(85)
LUA_PROXY(86)
LUA_PROXY(87)
LUA_PROXY(88)
LUA_PROXY(89)
LUA_PROXY(90)
LUA_PROXY(91)
LUA_PROXY(92)
LUA_PROXY(93)
LUA_PROXY(94)
LUA_PROXY(95)
LUA_PROXY(96)
LUA_PROXY(97)
LUA_PROXY(98)
LUA_PROXY(99)
LUA_PROXY(100)
LUA_PROXY(101)
LUA_PROXY(102)
LUA_PROXY(103)
LUA_PROXY(104)
LUA_PROXY(105)
LUA_PROXY(106)
LUA_PROXY(107)
LUA_PROXY(108)
LUA_PROXY(109)
LUA_PROXY(110)
LUA_PROXY(111)
LUA_PROXY(112)
LUA_PROXY(113)
LUA_PROXY(114)
LUA_PROXY(115)
LUA_PROXY(116)
LUA_PROXY(117)
LUA_PROXY(118)
LUA_PROXY(119)
LUA_PROXY(120)
LUA_PROXY(121)
LUA_PROXY(122)
