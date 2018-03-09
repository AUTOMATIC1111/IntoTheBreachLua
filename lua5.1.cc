#include <windows.h>
#pragma pack(1)

static HINSTANCE libHandle = 0;
FARPROC luaTable[123] = { 0 };

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
	if(reason == DLL_PROCESS_DETACH) {
		FreeLibrary(libHandle);
	}

	if(reason != DLL_PROCESS_ATTACH) {
		return 1;
	}

	libHandle = LoadLibraryA("lua5.1-original.dll");
	if(!libHandle) return false;

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

// luaL_addlstring
extern "C" __declspec(naked) void __stdcall __E__0__() {
	__asm
	{
		jmp luaTable[0 * 4];
	}
}

// luaL_addstring
extern "C" __declspec(naked) void __stdcall __E__1__() {
	__asm
	{
		jmp luaTable[1 * 4];
	}
}

// luaL_addvalue
extern "C" __declspec(naked) void __stdcall __E__2__() {
	__asm
	{
		jmp luaTable[2 * 4];
	}
}

// luaL_argerror
extern "C" __declspec(naked) void __stdcall __E__3__() {
	__asm
	{
		jmp luaTable[3 * 4];
	}
}

// luaL_buffinit
extern "C" __declspec(naked) void __stdcall __E__4__() {
	__asm
	{
		jmp luaTable[4 * 4];
	}
}

// luaL_callmeta
extern "C" __declspec(naked) void __stdcall __E__5__() {
	__asm
	{
		jmp luaTable[5 * 4];
	}
}

// luaL_checkany
extern "C" __declspec(naked) void __stdcall __E__6__() {
	__asm
	{
		jmp luaTable[6 * 4];
	}
}

// luaL_checkinteger
extern "C" __declspec(naked) void __stdcall __E__7__() {
	__asm
	{
		jmp luaTable[7 * 4];
	}
}

// luaL_checklstring
extern "C" __declspec(naked) void __stdcall __E__8__() {
	__asm
	{
		jmp luaTable[8 * 4];
	}
}

// luaL_checknumber
extern "C" __declspec(naked) void __stdcall __E__9__() {
	__asm
	{
		jmp luaTable[9 * 4];
	}
}

// luaL_checkoption
extern "C" __declspec(naked) void __stdcall __E__10__() {
	__asm
	{
		jmp luaTable[10 * 4];
	}
}

// luaL_checkstack
extern "C" __declspec(naked) void __stdcall __E__11__() {
	__asm
	{
		jmp luaTable[11 * 4];
	}
}

// luaL_checktype
extern "C" __declspec(naked) void __stdcall __E__12__() {
	__asm
	{
		jmp luaTable[12 * 4];
	}
}

// luaL_checkudata
extern "C" __declspec(naked) void __stdcall __E__13__() {
	__asm
	{
		jmp luaTable[13 * 4];
	}
}

// luaL_error
extern "C" __declspec(naked) void __stdcall __E__14__() {
	__asm
	{
		jmp luaTable[14 * 4];
	}
}

// luaL_findtable
extern "C" __declspec(naked) void __stdcall __E__15__() {
	__asm
	{
		jmp luaTable[15 * 4];
	}
}

// luaL_getmetafield
extern "C" __declspec(naked) void __stdcall __E__16__() {
	__asm
	{
		jmp luaTable[16 * 4];
	}
}

// luaL_gsub
extern "C" __declspec(naked) void __stdcall __E__17__() {
	__asm
	{
		jmp luaTable[17 * 4];
	}
}

// luaL_loadbuffer
extern "C" __declspec(naked) void __stdcall __E__18__() {
	__asm
	{
		jmp luaTable[18 * 4];
	}
}

// luaL_loadfile
extern "C" __declspec(naked) void __stdcall __E__19__() {
	__asm
	{
		jmp luaTable[19 * 4];
	}
}

// luaL_loadstring
extern "C" __declspec(naked) void __stdcall __E__20__() {
	__asm
	{
		jmp luaTable[20 * 4];
	}
}

// luaL_newmetatable
extern "C" __declspec(naked) void __stdcall __E__21__() {
	__asm
	{
		jmp luaTable[21 * 4];
	}
}


// luaL_newstate
extern "C" __declspec(naked) void __stdcall __E__22__() {
	__asm
	{
		jmp luaTable[22 * 4];
	}
}


// luaL_openlib
extern "C" __declspec(naked) void __stdcall __E__23__() {
	__asm
	{
		jmp luaTable[23 * 4];
	}
}

// luaL_openlibs
extern "C" __declspec(naked) void __stdcall __E__24__() {
	__asm
	{
		jmp luaTable[24 * 4];
	}
}

// luaL_optinteger
extern "C" __declspec(naked) void __stdcall __E__25__() {
	__asm
	{
		jmp luaTable[25 * 4];
	}
}

// luaL_optlstring
extern "C" __declspec(naked) void __stdcall __E__26__() {
	__asm
	{
		jmp luaTable[26 * 4];
	}
}

// luaL_optnumber
extern "C" __declspec(naked) void __stdcall __E__27__() {
	__asm
	{
		jmp luaTable[27 * 4];
	}
}

// luaL_prepbuffer
extern "C" __declspec(naked) void __stdcall __E__28__() {
	__asm
	{
		jmp luaTable[28 * 4];
	}
}

// luaL_pushresult
extern "C" __declspec(naked) void __stdcall __E__29__() {
	__asm
	{
		jmp luaTable[29 * 4];
	}
}

// luaL_ref
extern "C" __declspec(naked) void __stdcall __E__30__() {
	__asm
	{
		jmp luaTable[30 * 4];
	}
}

// luaL_register
extern "C" __declspec(naked) void __stdcall __E__31__() {
	__asm
	{
		jmp luaTable[31 * 4];
	}
}

// luaL_typerror
extern "C" __declspec(naked) void __stdcall __E__32__() {
	__asm
	{
		jmp luaTable[32 * 4];
	}
}

// luaL_unref
extern "C" __declspec(naked) void __stdcall __E__33__() {
	__asm
	{
		jmp luaTable[33 * 4];
	}
}

// luaL_where
extern "C" __declspec(naked) void __stdcall __E__34__() {
	__asm
	{
		jmp luaTable[34 * 4];
	}
}

// lua_atpanic
extern "C" __declspec(naked) void __stdcall __E__35__() {
	__asm
	{
		jmp luaTable[35 * 4];
	}
}

// lua_call
extern "C" __declspec(naked) void __stdcall __E__36__() {
	__asm
	{
		jmp luaTable[36 * 4];
	}
}

// lua_checkstack
extern "C" __declspec(naked) void __stdcall __E__37__() {
	__asm
	{
		jmp luaTable[37 * 4];
	}
}

// lua_close
extern "C" __declspec(naked) void __stdcall __E__38__() {
	__asm
	{
		jmp luaTable[38 * 4];
	}
}

// lua_concat
extern "C" __declspec(naked) void __stdcall __E__39__() {
	__asm
	{
		jmp luaTable[39 * 4];
	}
}

// lua_cpcall
extern "C" __declspec(naked) void __stdcall __E__40__() {
	__asm
	{
		jmp luaTable[40 * 4];
	}
}

// lua_createtable
extern "C" __declspec(naked) void __stdcall __E__41__() {
	__asm
	{
		jmp luaTable[41 * 4];
	}
}

// lua_dump
extern "C" __declspec(naked) void __stdcall __E__42__() {
	__asm
	{
		jmp luaTable[42 * 4];
	}
}

// lua_equal
extern "C" __declspec(naked) void __stdcall __E__43__() {
	__asm
	{
		jmp luaTable[43 * 4];
	}
}

// lua_error
extern "C" __declspec(naked) void __stdcall __E__44__() {
	__asm
	{
		jmp luaTable[44 * 4];
	}
}

// lua_gc
extern "C" __declspec(naked) void __stdcall __E__45__() {
	__asm
	{
		jmp luaTable[45 * 4];
	}
}

// lua_getallocf
extern "C" __declspec(naked) void __stdcall __E__46__() {
	__asm
	{
		jmp luaTable[46 * 4];
	}
}

// lua_getfenv
extern "C" __declspec(naked) void __stdcall __E__47__() {
	__asm
	{
		jmp luaTable[47 * 4];
	}
}

// lua_getfield
extern "C" __declspec(naked) void __stdcall __E__48__() {
	__asm
	{
		jmp luaTable[48 * 4];
	}
}

// lua_gethook
extern "C" __declspec(naked) void __stdcall __E__49__() {
	__asm
	{
		jmp luaTable[49 * 4];
	}
}

// lua_gethookcount
extern "C" __declspec(naked) void __stdcall __E__50__() {
	__asm
	{
		jmp luaTable[50 * 4];
	}
}

// lua_gethookmask
extern "C" __declspec(naked) void __stdcall __E__51__() {
	__asm
	{
		jmp luaTable[51 * 4];
	}
}

// lua_getinfo
extern "C" __declspec(naked) void __stdcall __E__52__() {
	__asm
	{
		jmp luaTable[52 * 4];
	}
}

// lua_getlocal
extern "C" __declspec(naked) void __stdcall __E__53__() {
	__asm
	{
		jmp luaTable[53 * 4];
	}
}

// lua_getmetatable
extern "C" __declspec(naked) void __stdcall __E__54__() {
	__asm
	{
		jmp luaTable[54 * 4];
	}
}

// lua_getstack
extern "C" __declspec(naked) void __stdcall __E__55__() {
	__asm
	{
		jmp luaTable[55 * 4];
	}
}

// lua_gettable
extern "C" __declspec(naked) void __stdcall __E__56__() {
	__asm
	{
		jmp luaTable[56 * 4];
	}
}

// lua_gettop
extern "C" __declspec(naked) void __stdcall __E__57__() {
	__asm
	{
		jmp luaTable[57 * 4];
	}
}

// lua_getupvalue
extern "C" __declspec(naked) void __stdcall __E__58__() {
	__asm
	{
		jmp luaTable[58 * 4];
	}
}

// lua_insert
extern "C" __declspec(naked) void __stdcall __E__59__() {
	__asm
	{
		jmp luaTable[59 * 4];
	}
}

// lua_iscfunction
extern "C" __declspec(naked) void __stdcall __E__60__() {
	__asm
	{
		jmp luaTable[60 * 4];
	}
}

// lua_isnumber
extern "C" __declspec(naked) void __stdcall __E__61__() {
	__asm
	{
		jmp luaTable[61 * 4];
	}
}

// lua_isstring
extern "C" __declspec(naked) void __stdcall __E__62__() {
	__asm
	{
		jmp luaTable[62 * 4];
	}
}

// lua_isuserdata
extern "C" __declspec(naked) void __stdcall __E__63__() {
	__asm
	{
		jmp luaTable[63 * 4];
	}
}

// lua_lessthan
extern "C" __declspec(naked) void __stdcall __E__64__() {
	__asm
	{
		jmp luaTable[64 * 4];
	}
}

// lua_load
extern "C" __declspec(naked) void __stdcall __E__65__() {
	__asm
	{
		jmp luaTable[65 * 4];
	}
}

// lua_newstate
extern "C" __declspec(naked) void __stdcall __E__66__() {
	__asm
	{
		jmp luaTable[66 * 4];
	}
}

// lua_newthread
extern "C" __declspec(naked) void __stdcall __E__67__() {
	__asm
	{
		jmp luaTable[67 * 4];
	}
}

// lua_newuserdata
extern "C" __declspec(naked) void __stdcall __E__68__() {
	__asm
	{
		jmp luaTable[68 * 4];
	}
}

// lua_next
extern "C" __declspec(naked) void __stdcall __E__69__() {
	__asm
	{
		jmp luaTable[69 * 4];
	}
}

// lua_objlen
extern "C" __declspec(naked) void __stdcall __E__70__() {
	__asm
	{
		jmp luaTable[70 * 4];
	}
}

// lua_pcall
extern "C" __declspec(naked) void __stdcall __E__71__() {
	__asm
	{
		jmp luaTable[71 * 4];
	}
}

// lua_pushboolean
extern "C" __declspec(naked) void __stdcall __E__72__() {
	__asm
	{
		jmp luaTable[72 * 4];
	}
}

// lua_pushcclosure
extern "C" __declspec(naked) void __stdcall __E__73__() {
	__asm
	{
		jmp luaTable[73 * 4];
	}
}

// lua_pushfstring
extern "C" __declspec(naked) void __stdcall __E__74__() {
	__asm
	{
		jmp luaTable[74 * 4];
	}
}

// lua_pushinteger
extern "C" __declspec(naked) void __stdcall __E__75__() {
	__asm
	{
		jmp luaTable[75 * 4];
	}
}

// lua_pushlightuserdata
extern "C" __declspec(naked) void __stdcall __E__76__() {
	__asm
	{
		jmp luaTable[76 * 4];
	}
}

// lua_pushlstring
extern "C" __declspec(naked) void __stdcall __E__77__() {
	__asm
	{
		jmp luaTable[77 * 4];
	}
}

// lua_pushnil
extern "C" __declspec(naked) void __stdcall __E__78__() {
	__asm
	{
		jmp luaTable[78 * 4];
	}
}

// lua_pushnumber
extern "C" __declspec(naked) void __stdcall __E__79__() {
	__asm
	{
		jmp luaTable[79 * 4];
	}
}

// lua_pushstring
extern "C" __declspec(naked) void __stdcall __E__80__() {
	__asm
	{
		jmp luaTable[80 * 4];
	}
}

// lua_pushthread
extern "C" __declspec(naked) void __stdcall __E__81__() {
	__asm
	{
		jmp luaTable[81 * 4];
	}
}

// lua_pushvalue
extern "C" __declspec(naked) void __stdcall __E__82__() {
	__asm
	{
		jmp luaTable[82 * 4];
	}
}

// lua_pushvfstring
extern "C" __declspec(naked) void __stdcall __E__83__() {
	__asm
	{
		jmp luaTable[83 * 4];
	}
}

// lua_rawequal
extern "C" __declspec(naked) void __stdcall __E__84__() {
	__asm
	{
		jmp luaTable[84 * 4];
	}
}

// lua_rawget
extern "C" __declspec(naked) void __stdcall __E__85__() {
	__asm
	{
		jmp luaTable[85 * 4];
	}
}

// lua_rawgeti
extern "C" __declspec(naked) void __stdcall __E__86__() {
	__asm
	{
		jmp luaTable[86 * 4];
	}
}

// lua_rawset
extern "C" __declspec(naked) void __stdcall __E__87__() {
	__asm
	{
		jmp luaTable[87 * 4];
	}
}

// lua_rawseti
extern "C" __declspec(naked) void __stdcall __E__88__() {
	__asm
	{
		jmp luaTable[88 * 4];
	}
}

// lua_remove
extern "C" __declspec(naked) void __stdcall __E__89__() {
	__asm
	{
		jmp luaTable[89 * 4];
	}
}

// lua_replace
extern "C" __declspec(naked) void __stdcall __E__90__() {
	__asm
	{
		jmp luaTable[90 * 4];
	}
}

// lua_resume
extern "C" __declspec(naked) void __stdcall __E__91__() {
	__asm
	{
		jmp luaTable[91 * 4];
	}
}

// lua_setallocf
extern "C" __declspec(naked) void __stdcall __E__92__() {
	__asm
	{
		jmp luaTable[92 * 4];
	}
}

// lua_setfenv
extern "C" __declspec(naked) void __stdcall __E__93__() {
	__asm
	{
		jmp luaTable[93 * 4];
	}
}

// lua_setfield
extern "C" __declspec(naked) void __stdcall __E__94__() {
	__asm
	{
		jmp luaTable[94 * 4];
	}
}

// lua_sethook
extern "C" __declspec(naked) void __stdcall __E__95__() {
	__asm
	{
		jmp luaTable[95 * 4];
	}
}

// lua_setlevel
extern "C" __declspec(naked) void __stdcall __E__96__() {
	__asm
	{
		jmp luaTable[96 * 4];
	}
}

// lua_setlocal
extern "C" __declspec(naked) void __stdcall __E__97__() {
	__asm
	{
		jmp luaTable[97 * 4];
	}
}

// lua_setmetatable
extern "C" __declspec(naked) void __stdcall __E__98__() {
	__asm
	{
		jmp luaTable[98 * 4];
	}
}

// lua_settable
extern "C" __declspec(naked) void __stdcall __E__99__() {
	__asm
	{
		jmp luaTable[99 * 4];
	}
}

// lua_settop
extern "C" __declspec(naked) void __stdcall __E__100__() {
	__asm
	{
		jmp luaTable[100 * 4];
	}
}

// lua_setupvalue
extern "C" __declspec(naked) void __stdcall __E__101__() {
	__asm
	{
		jmp luaTable[101 * 4];
	}
}

// lua_status
extern "C" __declspec(naked) void __stdcall __E__102__() {
	__asm
	{
		jmp luaTable[102 * 4];
	}
}

// lua_toboolean
extern "C" __declspec(naked) void __stdcall __E__103__() {
	__asm
	{
		jmp luaTable[103 * 4];
	}
}

// lua_tocfunction
extern "C" __declspec(naked) void __stdcall __E__104__() {
	__asm
	{
		jmp luaTable[104 * 4];
	}
}

// lua_tointeger
extern "C" __declspec(naked) void __stdcall __E__105__() {
	__asm
	{
		jmp luaTable[105 * 4];
	}
}

// lua_tolstring
extern "C" __declspec(naked) void __stdcall __E__106__() {
	__asm
	{
		jmp luaTable[106 * 4];
	}
}

// lua_tonumber
extern "C" __declspec(naked) void __stdcall __E__107__() {
	__asm
	{
		jmp luaTable[107 * 4];
	}
}

// lua_topointer
extern "C" __declspec(naked) void __stdcall __E__108__() {
	__asm
	{
		jmp luaTable[108 * 4];
	}
}

// lua_tothread
extern "C" __declspec(naked) void __stdcall __E__109__() {
	__asm
	{
		jmp luaTable[109 * 4];
	}
}

// lua_touserdata
extern "C" __declspec(naked) void __stdcall __E__110__() {
	__asm
	{
		jmp luaTable[110 * 4];
	}
}

// lua_type
extern "C" __declspec(naked) void __stdcall __E__111__() {
	__asm
	{
		jmp luaTable[111 * 4];
	}
}

// lua_typename
extern "C" __declspec(naked) void __stdcall __E__112__() {
	__asm
	{
		jmp luaTable[112 * 4];
	}
}

// lua_xmove
extern "C" __declspec(naked) void __stdcall __E__113__() {
	__asm
	{
		jmp luaTable[113 * 4];
	}
}

// lua_yield
extern "C" __declspec(naked) void __stdcall __E__114__() {
	__asm
	{
		jmp luaTable[114 * 4];
	}
}

// luaopen_base
extern "C" __declspec(naked) void __stdcall __E__115__() {
	__asm
	{
		jmp luaTable[115 * 4];
	}
}

// luaopen_debug
extern "C" __declspec(naked) void __stdcall __E__116__() {
	__asm
	{
		jmp luaTable[116 * 4];
	}
}

// luaopen_io
extern "C" __declspec(naked) void __stdcall __E__117__() {
	__asm
	{
		jmp luaTable[117 * 4];
	}
}

// luaopen_math
extern "C" __declspec(naked) void __stdcall __E__118__() {
	__asm
	{
		jmp luaTable[118 * 4];
	}
}

// luaopen_os
extern "C" __declspec(naked) void __stdcall __E__119__() {
	__asm
	{
		jmp luaTable[119 * 4];
	}
}

// luaopen_package
extern "C" __declspec(naked) void __stdcall __E__120__() {
	__asm
	{
		jmp luaTable[120 * 4];
	}
}

// luaopen_string
extern "C" __declspec(naked) void __stdcall __E__121__() {
	__asm
	{
		jmp luaTable[121 * 4];
	}
}

// luaopen_table
extern "C" __declspec(naked) void __stdcall __E__122__() {
	__asm
	{
		jmp luaTable[122 * 4];
	}
}

