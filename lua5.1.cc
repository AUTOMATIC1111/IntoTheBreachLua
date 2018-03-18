#include <windows.h>
#include "opengl32.h"
#include "sdl2.h"
#include "sdl-utils.h"
#include "utils.h"
#pragma pack(1)

static HINSTANCE luaHandle = 0;
FARPROC luaTable[123] = { 0 };

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
	if(reason == DLL_PROCESS_DETACH) {
		FreeLibrary(luaHandle);
	}

	if(reason != DLL_PROCESS_ATTACH) {
		return 1;
	}

	installSdlHooks();

	luaHandle = LoadLibraryA("lua5.1-original.dll");
	if(!luaHandle) return false;

	installOpenglHooks();
	
	luaTable[0] = GetProcAddress(luaHandle, "luaL_addlstring");
	luaTable[1] = GetProcAddress(luaHandle, "luaL_addstring");
	luaTable[2] = GetProcAddress(luaHandle, "luaL_addvalue");
	luaTable[3] = GetProcAddress(luaHandle, "luaL_argerror");
	luaTable[4] = GetProcAddress(luaHandle, "luaL_buffinit");
	luaTable[5] = GetProcAddress(luaHandle, "luaL_callmeta");
	luaTable[6] = GetProcAddress(luaHandle, "luaL_checkany");
	luaTable[7] = GetProcAddress(luaHandle, "luaL_checkinteger");
	luaTable[8] = GetProcAddress(luaHandle, "luaL_checklstring");
	luaTable[9] = GetProcAddress(luaHandle, "luaL_checknumber");
	luaTable[10] = GetProcAddress(luaHandle, "luaL_checkoption");
	luaTable[11] = GetProcAddress(luaHandle, "luaL_checkstack");
	luaTable[12] = GetProcAddress(luaHandle, "luaL_checktype");
	luaTable[13] = GetProcAddress(luaHandle, "luaL_checkudata");
	luaTable[14] = GetProcAddress(luaHandle, "luaL_error");
	luaTable[15] = GetProcAddress(luaHandle, "luaL_findtable");
	luaTable[16] = GetProcAddress(luaHandle, "luaL_getmetafield");
	luaTable[17] = GetProcAddress(luaHandle, "luaL_gsub");
	luaTable[18] = GetProcAddress(luaHandle, "luaL_loadbuffer");
	luaTable[19] = GetProcAddress(luaHandle, "luaL_loadfile");
	luaTable[20] = GetProcAddress(luaHandle, "luaL_loadstring");
	luaTable[21] = GetProcAddress(luaHandle, "luaL_newmetatable");
	luaTable[22] = GetProcAddress(luaHandle, "luaL_newstate");
	luaTable[23] = GetProcAddress(luaHandle, "luaL_openlib");
	luaTable[24] = GetProcAddress(luaHandle, "luaL_openlibs");
	luaTable[25] = GetProcAddress(luaHandle, "luaL_optinteger");
	luaTable[26] = GetProcAddress(luaHandle, "luaL_optlstring");
	luaTable[27] = GetProcAddress(luaHandle, "luaL_optnumber");
	luaTable[28] = GetProcAddress(luaHandle, "luaL_prepbuffer");
	luaTable[29] = GetProcAddress(luaHandle, "luaL_pushresult");
	luaTable[30] = GetProcAddress(luaHandle, "luaL_ref");
	luaTable[31] = GetProcAddress(luaHandle, "luaL_register");
	luaTable[32] = GetProcAddress(luaHandle, "luaL_typerror");
	luaTable[33] = GetProcAddress(luaHandle, "luaL_unref");
	luaTable[34] = GetProcAddress(luaHandle, "luaL_where");
	luaTable[35] = GetProcAddress(luaHandle, "lua_atpanic");
	luaTable[36] = GetProcAddress(luaHandle, "lua_call");
	luaTable[37] = GetProcAddress(luaHandle, "lua_checkstack");
	luaTable[38] = GetProcAddress(luaHandle, "lua_close");
	luaTable[39] = GetProcAddress(luaHandle, "lua_concat");
	luaTable[40] = GetProcAddress(luaHandle, "lua_cpcall");
	luaTable[41] = GetProcAddress(luaHandle, "lua_createtable");
	luaTable[42] = GetProcAddress(luaHandle, "lua_dump");
	luaTable[43] = GetProcAddress(luaHandle, "lua_equal");
	luaTable[44] = GetProcAddress(luaHandle, "lua_error");
	luaTable[45] = GetProcAddress(luaHandle, "lua_gc");
	luaTable[46] = GetProcAddress(luaHandle, "lua_getallocf");
	luaTable[47] = GetProcAddress(luaHandle, "lua_getfenv");
	luaTable[48] = GetProcAddress(luaHandle, "lua_getfield");
	luaTable[49] = GetProcAddress(luaHandle, "lua_gethook");
	luaTable[50] = GetProcAddress(luaHandle, "lua_gethookcount");
	luaTable[51] = GetProcAddress(luaHandle, "lua_gethookmask");
	luaTable[52] = GetProcAddress(luaHandle, "lua_getinfo");
	luaTable[53] = GetProcAddress(luaHandle, "lua_getlocal");
	luaTable[54] = GetProcAddress(luaHandle, "lua_getmetatable");
	luaTable[55] = GetProcAddress(luaHandle, "lua_getstack");
	luaTable[56] = GetProcAddress(luaHandle, "lua_gettable");
	luaTable[57] = GetProcAddress(luaHandle, "lua_gettop");
	luaTable[58] = GetProcAddress(luaHandle, "lua_getupvalue");
	luaTable[59] = GetProcAddress(luaHandle, "lua_insert");
	luaTable[60] = GetProcAddress(luaHandle, "lua_iscfunction");
	luaTable[61] = GetProcAddress(luaHandle, "lua_isnumber");
	luaTable[62] = GetProcAddress(luaHandle, "lua_isstring");
	luaTable[63] = GetProcAddress(luaHandle, "lua_isuserdata");
	luaTable[64] = GetProcAddress(luaHandle, "lua_lessthan");
	luaTable[65] = GetProcAddress(luaHandle, "lua_load");
	luaTable[66] = GetProcAddress(luaHandle, "lua_newstate");
	luaTable[67] = GetProcAddress(luaHandle, "lua_newthread");
	luaTable[68] = GetProcAddress(luaHandle, "lua_newuserdata");
	luaTable[69] = GetProcAddress(luaHandle, "lua_next");
	luaTable[70] = GetProcAddress(luaHandle, "lua_objlen");
	luaTable[71] = GetProcAddress(luaHandle, "lua_pcall");
	luaTable[72] = GetProcAddress(luaHandle, "lua_pushboolean");
	luaTable[73] = GetProcAddress(luaHandle, "lua_pushcclosure");
	luaTable[74] = GetProcAddress(luaHandle, "lua_pushfstring");
	luaTable[75] = GetProcAddress(luaHandle, "lua_pushinteger");
	luaTable[76] = GetProcAddress(luaHandle, "lua_pushlightuserdata");
	luaTable[77] = GetProcAddress(luaHandle, "lua_pushlstring");
	luaTable[78] = GetProcAddress(luaHandle, "lua_pushnil");
	luaTable[79] = GetProcAddress(luaHandle, "lua_pushnumber");
	luaTable[80] = GetProcAddress(luaHandle, "lua_pushstring");
	luaTable[81] = GetProcAddress(luaHandle, "lua_pushthread");
	luaTable[82] = GetProcAddress(luaHandle, "lua_pushvalue");
	luaTable[83] = GetProcAddress(luaHandle, "lua_pushvfstring");
	luaTable[84] = GetProcAddress(luaHandle, "lua_rawequal");
	luaTable[85] = GetProcAddress(luaHandle, "lua_rawget");
	luaTable[86] = GetProcAddress(luaHandle, "lua_rawgeti");
	luaTable[87] = GetProcAddress(luaHandle, "lua_rawset");
	luaTable[88] = GetProcAddress(luaHandle, "lua_rawseti");
	luaTable[89] = GetProcAddress(luaHandle, "lua_remove");
	luaTable[90] = GetProcAddress(luaHandle, "lua_replace");
	luaTable[91] = GetProcAddress(luaHandle, "lua_resume");
	luaTable[92] = GetProcAddress(luaHandle, "lua_setallocf");
	luaTable[93] = GetProcAddress(luaHandle, "lua_setfenv");
	luaTable[94] = GetProcAddress(luaHandle, "lua_setfield");
	luaTable[95] = GetProcAddress(luaHandle, "lua_sethook");
	luaTable[96] = GetProcAddress(luaHandle, "lua_setlevel");
	luaTable[97] = GetProcAddress(luaHandle, "lua_setlocal");
	luaTable[98] = GetProcAddress(luaHandle, "lua_setmetatable");
	luaTable[99] = GetProcAddress(luaHandle, "lua_settable");
	luaTable[100] = GetProcAddress(luaHandle, "lua_settop");
	luaTable[101] = GetProcAddress(luaHandle, "lua_setupvalue");
	luaTable[102] = GetProcAddress(luaHandle, "lua_status");
	luaTable[103] = GetProcAddress(luaHandle, "lua_toboolean");
	luaTable[104] = GetProcAddress(luaHandle, "lua_tocfunction");
	luaTable[105] = GetProcAddress(luaHandle, "lua_tointeger");
	luaTable[106] = GetProcAddress(luaHandle, "lua_tolstring");
	luaTable[107] = GetProcAddress(luaHandle, "lua_tonumber");
	luaTable[108] = GetProcAddress(luaHandle, "lua_topointer");
	luaTable[109] = GetProcAddress(luaHandle, "lua_tothread");
	luaTable[110] = GetProcAddress(luaHandle, "lua_touserdata");
	luaTable[111] = GetProcAddress(luaHandle, "lua_type");
	luaTable[112] = GetProcAddress(luaHandle, "lua_typename");
	luaTable[113] = GetProcAddress(luaHandle, "lua_xmove");
	luaTable[114] = GetProcAddress(luaHandle, "lua_yield");
	luaTable[115] = GetProcAddress(luaHandle, "luaopen_base");
	luaTable[116] = GetProcAddress(luaHandle, "luaopen_debug");
	luaTable[117] = GetProcAddress(luaHandle, "luaopen_io");
	luaTable[118] = GetProcAddress(luaHandle, "luaopen_math");
	luaTable[119] = GetProcAddress(luaHandle, "luaopen_os");
	luaTable[120] = GetProcAddress(luaHandle, "luaopen_package");
	luaTable[121] = GetProcAddress(luaHandle, "luaopen_string");
	luaTable[122] = GetProcAddress(luaHandle, "luaopen_table");

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
