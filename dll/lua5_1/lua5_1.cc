#include <windows.h>
#pragma pack(1)

static HINSTANCE lua5_1Handle = 0;
FARPROC lua5_1Table[123] = { 0 };

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
	if(reason == DLL_PROCESS_DETACH && lua5_1Handle!=NULL) {
		FreeLibrary(lua5_1Handle);
		return 0;
	}

	if(reason != DLL_PROCESS_ATTACH) {
		return 1;
	}

	lua5_1Handle = LoadLibraryA("SDL2.dll");
	if(lua5_1Handle==NULL) return 1;
	
	lua5_1Table[0] = GetProcAddress(lua5_1Handle, "luaL_addlstring");
	lua5_1Table[1] = GetProcAddress(lua5_1Handle, "luaL_addstring");
	lua5_1Table[2] = GetProcAddress(lua5_1Handle, "luaL_addvalue");
	lua5_1Table[3] = GetProcAddress(lua5_1Handle, "luaL_argerror");
	lua5_1Table[4] = GetProcAddress(lua5_1Handle, "luaL_buffinit");
	lua5_1Table[5] = GetProcAddress(lua5_1Handle, "luaL_callmeta");
	lua5_1Table[6] = GetProcAddress(lua5_1Handle, "luaL_checkany");
	lua5_1Table[7] = GetProcAddress(lua5_1Handle, "luaL_checkinteger");
	lua5_1Table[8] = GetProcAddress(lua5_1Handle, "luaL_checklstring");
	lua5_1Table[9] = GetProcAddress(lua5_1Handle, "luaL_checknumber");
	lua5_1Table[10] = GetProcAddress(lua5_1Handle, "luaL_checkoption");
	lua5_1Table[11] = GetProcAddress(lua5_1Handle, "luaL_checkstack");
	lua5_1Table[12] = GetProcAddress(lua5_1Handle, "luaL_checktype");
	lua5_1Table[13] = GetProcAddress(lua5_1Handle, "luaL_checkudata");
	lua5_1Table[14] = GetProcAddress(lua5_1Handle, "luaL_error");
	lua5_1Table[15] = GetProcAddress(lua5_1Handle, "luaL_findtable");
	lua5_1Table[16] = GetProcAddress(lua5_1Handle, "luaL_getmetafield");
	lua5_1Table[17] = GetProcAddress(lua5_1Handle, "luaL_gsub");
	lua5_1Table[18] = GetProcAddress(lua5_1Handle, "luaL_loadbuffer");
	lua5_1Table[19] = GetProcAddress(lua5_1Handle, "luaL_loadfile");
	lua5_1Table[20] = GetProcAddress(lua5_1Handle, "luaL_loadstring");
	lua5_1Table[21] = GetProcAddress(lua5_1Handle, "luaL_newmetatable");
	lua5_1Table[22] = GetProcAddress(lua5_1Handle, "luaL_newstate");
	lua5_1Table[23] = GetProcAddress(lua5_1Handle, "luaL_openlib");
	lua5_1Table[24] = GetProcAddress(lua5_1Handle, "luaL_openlibs");
	lua5_1Table[25] = GetProcAddress(lua5_1Handle, "luaL_optinteger");
	lua5_1Table[26] = GetProcAddress(lua5_1Handle, "luaL_optlstring");
	lua5_1Table[27] = GetProcAddress(lua5_1Handle, "luaL_optnumber");
	lua5_1Table[28] = GetProcAddress(lua5_1Handle, "luaL_prepbuffer");
	lua5_1Table[29] = GetProcAddress(lua5_1Handle, "luaL_pushresult");
	lua5_1Table[30] = GetProcAddress(lua5_1Handle, "luaL_ref");
	lua5_1Table[31] = GetProcAddress(lua5_1Handle, "luaL_register");
	lua5_1Table[32] = GetProcAddress(lua5_1Handle, "luaL_typerror");
	lua5_1Table[33] = GetProcAddress(lua5_1Handle, "luaL_unref");
	lua5_1Table[34] = GetProcAddress(lua5_1Handle, "luaL_where");
	lua5_1Table[35] = GetProcAddress(lua5_1Handle, "lua_atpanic");
	lua5_1Table[36] = GetProcAddress(lua5_1Handle, "lua_call");
	lua5_1Table[37] = GetProcAddress(lua5_1Handle, "lua_checkstack");
	lua5_1Table[38] = GetProcAddress(lua5_1Handle, "lua_close");
	lua5_1Table[39] = GetProcAddress(lua5_1Handle, "lua_concat");
	lua5_1Table[40] = GetProcAddress(lua5_1Handle, "lua_cpcall");
	lua5_1Table[41] = GetProcAddress(lua5_1Handle, "lua_createtable");
	lua5_1Table[42] = GetProcAddress(lua5_1Handle, "lua_dump");
	lua5_1Table[43] = GetProcAddress(lua5_1Handle, "lua_equal");
	lua5_1Table[44] = GetProcAddress(lua5_1Handle, "lua_error");
	lua5_1Table[45] = GetProcAddress(lua5_1Handle, "lua_gc");
	lua5_1Table[46] = GetProcAddress(lua5_1Handle, "lua_getallocf");
	lua5_1Table[47] = GetProcAddress(lua5_1Handle, "lua_getfenv");
	lua5_1Table[48] = GetProcAddress(lua5_1Handle, "lua_getfield");
	lua5_1Table[49] = GetProcAddress(lua5_1Handle, "lua_gethook");
	lua5_1Table[50] = GetProcAddress(lua5_1Handle, "lua_gethookcount");
	lua5_1Table[51] = GetProcAddress(lua5_1Handle, "lua_gethookmask");
	lua5_1Table[52] = GetProcAddress(lua5_1Handle, "lua_getinfo");
	lua5_1Table[53] = GetProcAddress(lua5_1Handle, "lua_getlocal");
	lua5_1Table[54] = GetProcAddress(lua5_1Handle, "lua_getmetatable");
	lua5_1Table[55] = GetProcAddress(lua5_1Handle, "lua_getstack");
	lua5_1Table[56] = GetProcAddress(lua5_1Handle, "lua_gettable");
	lua5_1Table[57] = GetProcAddress(lua5_1Handle, "lua_gettop");
	lua5_1Table[58] = GetProcAddress(lua5_1Handle, "lua_getupvalue");
	lua5_1Table[59] = GetProcAddress(lua5_1Handle, "lua_insert");
	lua5_1Table[60] = GetProcAddress(lua5_1Handle, "lua_iscfunction");
	lua5_1Table[61] = GetProcAddress(lua5_1Handle, "lua_isnumber");
	lua5_1Table[62] = GetProcAddress(lua5_1Handle, "lua_isstring");
	lua5_1Table[63] = GetProcAddress(lua5_1Handle, "lua_isuserdata");
	lua5_1Table[64] = GetProcAddress(lua5_1Handle, "lua_lessthan");
	lua5_1Table[65] = GetProcAddress(lua5_1Handle, "lua_load");
	lua5_1Table[66] = GetProcAddress(lua5_1Handle, "lua_newstate");
	lua5_1Table[67] = GetProcAddress(lua5_1Handle, "lua_newthread");
	lua5_1Table[68] = GetProcAddress(lua5_1Handle, "lua_newuserdata");
	lua5_1Table[69] = GetProcAddress(lua5_1Handle, "lua_next");
	lua5_1Table[70] = GetProcAddress(lua5_1Handle, "lua_objlen");
	lua5_1Table[71] = GetProcAddress(lua5_1Handle, "lua_pcall");
	lua5_1Table[72] = GetProcAddress(lua5_1Handle, "lua_pushboolean");
	lua5_1Table[73] = GetProcAddress(lua5_1Handle, "lua_pushcclosure");
	lua5_1Table[74] = GetProcAddress(lua5_1Handle, "lua_pushfstring");
	lua5_1Table[75] = GetProcAddress(lua5_1Handle, "lua_pushinteger");
	lua5_1Table[76] = GetProcAddress(lua5_1Handle, "lua_pushlightuserdata");
	lua5_1Table[77] = GetProcAddress(lua5_1Handle, "lua_pushlstring");
	lua5_1Table[78] = GetProcAddress(lua5_1Handle, "lua_pushnil");
	lua5_1Table[79] = GetProcAddress(lua5_1Handle, "lua_pushnumber");
	lua5_1Table[80] = GetProcAddress(lua5_1Handle, "lua_pushstring");
	lua5_1Table[81] = GetProcAddress(lua5_1Handle, "lua_pushthread");
	lua5_1Table[82] = GetProcAddress(lua5_1Handle, "lua_pushvalue");
	lua5_1Table[83] = GetProcAddress(lua5_1Handle, "lua_pushvfstring");
	lua5_1Table[84] = GetProcAddress(lua5_1Handle, "lua_rawequal");
	lua5_1Table[85] = GetProcAddress(lua5_1Handle, "lua_rawget");
	lua5_1Table[86] = GetProcAddress(lua5_1Handle, "lua_rawgeti");
	lua5_1Table[87] = GetProcAddress(lua5_1Handle, "lua_rawset");
	lua5_1Table[88] = GetProcAddress(lua5_1Handle, "lua_rawseti");
	lua5_1Table[89] = GetProcAddress(lua5_1Handle, "lua_remove");
	lua5_1Table[90] = GetProcAddress(lua5_1Handle, "lua_replace");
	lua5_1Table[91] = GetProcAddress(lua5_1Handle, "lua_resume");
	lua5_1Table[92] = GetProcAddress(lua5_1Handle, "lua_setallocf");
	lua5_1Table[93] = GetProcAddress(lua5_1Handle, "lua_setfenv");
	lua5_1Table[94] = GetProcAddress(lua5_1Handle, "lua_setfield");
	lua5_1Table[95] = GetProcAddress(lua5_1Handle, "lua_sethook");
	lua5_1Table[96] = GetProcAddress(lua5_1Handle, "lua_setlevel");
	lua5_1Table[97] = GetProcAddress(lua5_1Handle, "lua_setlocal");
	lua5_1Table[98] = GetProcAddress(lua5_1Handle, "lua_setmetatable");
	lua5_1Table[99] = GetProcAddress(lua5_1Handle, "lua_settable");
	lua5_1Table[100] = GetProcAddress(lua5_1Handle, "lua_settop");
	lua5_1Table[101] = GetProcAddress(lua5_1Handle, "lua_setupvalue");
	lua5_1Table[102] = GetProcAddress(lua5_1Handle, "lua_status");
	lua5_1Table[103] = GetProcAddress(lua5_1Handle, "lua_toboolean");
	lua5_1Table[104] = GetProcAddress(lua5_1Handle, "lua_tocfunction");
	lua5_1Table[105] = GetProcAddress(lua5_1Handle, "lua_tointeger");
	lua5_1Table[106] = GetProcAddress(lua5_1Handle, "lua_tolstring");
	lua5_1Table[107] = GetProcAddress(lua5_1Handle, "lua_tonumber");
	lua5_1Table[108] = GetProcAddress(lua5_1Handle, "lua_topointer");
	lua5_1Table[109] = GetProcAddress(lua5_1Handle, "lua_tothread");
	lua5_1Table[110] = GetProcAddress(lua5_1Handle, "lua_touserdata");
	lua5_1Table[111] = GetProcAddress(lua5_1Handle, "lua_type");
	lua5_1Table[112] = GetProcAddress(lua5_1Handle, "lua_typename");
	lua5_1Table[113] = GetProcAddress(lua5_1Handle, "lua_xmove");
	lua5_1Table[114] = GetProcAddress(lua5_1Handle, "lua_yield");
	lua5_1Table[115] = GetProcAddress(lua5_1Handle, "luaopen_base");
	lua5_1Table[116] = GetProcAddress(lua5_1Handle, "luaopen_debug");
	lua5_1Table[117] = GetProcAddress(lua5_1Handle, "luaopen_io");
	lua5_1Table[118] = GetProcAddress(lua5_1Handle, "luaopen_math");
	lua5_1Table[119] = GetProcAddress(lua5_1Handle, "luaopen_os");
	lua5_1Table[120] = GetProcAddress(lua5_1Handle, "luaopen_package");
	lua5_1Table[121] = GetProcAddress(lua5_1Handle, "luaopen_string");
	lua5_1Table[122] = GetProcAddress(lua5_1Handle, "luaopen_table");

	return 1;
}

#define PROXY(n) extern "C" __declspec(naked) void __stdcall __L__##n##__() { { __asm jmp lua5_1Table[n * 4] } }
PROXY(0)
PROXY(1)
PROXY(2)
PROXY(3)
PROXY(4)
PROXY(5)
PROXY(6)
PROXY(7)
PROXY(8)
PROXY(9)
PROXY(10)
PROXY(11)
PROXY(12)
PROXY(13)
PROXY(14)
PROXY(15)
PROXY(16)
PROXY(17)
PROXY(18)
PROXY(19)
PROXY(20)
PROXY(21)
PROXY(22)
PROXY(23)
PROXY(24)
PROXY(25)
PROXY(26)
PROXY(27)
PROXY(28)
PROXY(29)
PROXY(30)
PROXY(31)
PROXY(32)
PROXY(33)
PROXY(34)
PROXY(35)
PROXY(36)
PROXY(37)
PROXY(38)
PROXY(39)
PROXY(40)
PROXY(41)
PROXY(42)
PROXY(43)
PROXY(44)
PROXY(45)
PROXY(46)
PROXY(47)
PROXY(48)
PROXY(49)
PROXY(50)
PROXY(51)
PROXY(52)
PROXY(53)
PROXY(54)
PROXY(55)
PROXY(56)
PROXY(57)
PROXY(58)
PROXY(59)
PROXY(60)
PROXY(61)
PROXY(62)
PROXY(63)
PROXY(64)
PROXY(65)
PROXY(66)
PROXY(67)
PROXY(68)
PROXY(69)
PROXY(70)
PROXY(71)
PROXY(72)
PROXY(73)
PROXY(74)
PROXY(75)
PROXY(76)
PROXY(77)
PROXY(78)
PROXY(79)
PROXY(80)
PROXY(81)
PROXY(82)
PROXY(83)
PROXY(84)
PROXY(85)
PROXY(86)
PROXY(87)
PROXY(88)
PROXY(89)
PROXY(90)
PROXY(91)
PROXY(92)
PROXY(93)
PROXY(94)
PROXY(95)
PROXY(96)
PROXY(97)
PROXY(98)
PROXY(99)
PROXY(100)
PROXY(101)
PROXY(102)
PROXY(103)
PROXY(104)
PROXY(105)
PROXY(106)
PROXY(107)
PROXY(108)
PROXY(109)
PROXY(110)
PROXY(111)
PROXY(112)
PROXY(113)
PROXY(114)
PROXY(115)
PROXY(116)
PROXY(117)
PROXY(118)
PROXY(119)
PROXY(120)
PROXY(121)
PROXY(122)
#undef PROXY
