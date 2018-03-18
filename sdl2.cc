#include <windows.h>
#pragma pack(1)

FARPROC sdl2Table[567] = { 0 };

bool installSdlHooks() {
	HINSTANCE sdl2Handle = LoadLibraryA("sdl2-original.dll");
	if(sdl2Handle==NULL) return false;
	
	sdl2Table[0] = GetProcAddress(sdl2Handle, "SDL_AddEventWatch");
	sdl2Table[1] = GetProcAddress(sdl2Handle, "SDL_AddHintCallback");
	sdl2Table[2] = GetProcAddress(sdl2Handle, "SDL_AddTimer");
	sdl2Table[3] = GetProcAddress(sdl2Handle, "SDL_AllocFormat");
	sdl2Table[4] = GetProcAddress(sdl2Handle, "SDL_AllocPalette");
	sdl2Table[5] = GetProcAddress(sdl2Handle, "SDL_AllocRW");
	sdl2Table[6] = GetProcAddress(sdl2Handle, "SDL_AtomicAdd");
	sdl2Table[7] = GetProcAddress(sdl2Handle, "SDL_AtomicCAS");
	sdl2Table[8] = GetProcAddress(sdl2Handle, "SDL_AtomicCASPtr");
	sdl2Table[9] = GetProcAddress(sdl2Handle, "SDL_AtomicGet");
	sdl2Table[10] = GetProcAddress(sdl2Handle, "SDL_AtomicGetPtr");
	sdl2Table[11] = GetProcAddress(sdl2Handle, "SDL_AtomicLock");
	sdl2Table[12] = GetProcAddress(sdl2Handle, "SDL_AtomicSet");
	sdl2Table[13] = GetProcAddress(sdl2Handle, "SDL_AtomicSetPtr");
	sdl2Table[14] = GetProcAddress(sdl2Handle, "SDL_AtomicTryLock");
	sdl2Table[15] = GetProcAddress(sdl2Handle, "SDL_AtomicUnlock");
	sdl2Table[16] = GetProcAddress(sdl2Handle, "SDL_AudioInit");
	sdl2Table[17] = GetProcAddress(sdl2Handle, "SDL_AudioQuit");
	sdl2Table[18] = GetProcAddress(sdl2Handle, "SDL_BuildAudioCVT");
	sdl2Table[19] = GetProcAddress(sdl2Handle, "SDL_CalculateGammaRamp");
	sdl2Table[20] = GetProcAddress(sdl2Handle, "SDL_CaptureMouse");
	sdl2Table[21] = GetProcAddress(sdl2Handle, "SDL_ClearError");
	sdl2Table[22] = GetProcAddress(sdl2Handle, "SDL_ClearHints");
	sdl2Table[23] = GetProcAddress(sdl2Handle, "SDL_ClearQueuedAudio");
	sdl2Table[24] = GetProcAddress(sdl2Handle, "SDL_CloseAudio");
	sdl2Table[25] = GetProcAddress(sdl2Handle, "SDL_CloseAudioDevice");
	sdl2Table[26] = GetProcAddress(sdl2Handle, "SDL_CondBroadcast");
	sdl2Table[27] = GetProcAddress(sdl2Handle, "SDL_CondSignal");
	sdl2Table[28] = GetProcAddress(sdl2Handle, "SDL_CondWait");
	sdl2Table[29] = GetProcAddress(sdl2Handle, "SDL_CondWaitTimeout");
	sdl2Table[30] = GetProcAddress(sdl2Handle, "SDL_ConvertAudio");
	sdl2Table[31] = GetProcAddress(sdl2Handle, "SDL_ConvertPixels");
	sdl2Table[32] = GetProcAddress(sdl2Handle, "SDL_ConvertSurface");
	sdl2Table[33] = GetProcAddress(sdl2Handle, "SDL_ConvertSurfaceFormat");
	sdl2Table[34] = GetProcAddress(sdl2Handle, "SDL_CreateColorCursor");
	sdl2Table[35] = GetProcAddress(sdl2Handle, "SDL_CreateCond");
	sdl2Table[36] = GetProcAddress(sdl2Handle, "SDL_CreateCursor");
	sdl2Table[37] = GetProcAddress(sdl2Handle, "SDL_CreateMutex");
	sdl2Table[38] = GetProcAddress(sdl2Handle, "SDL_CreateRGBSurface");
	sdl2Table[39] = GetProcAddress(sdl2Handle, "SDL_CreateRGBSurfaceFrom");
	sdl2Table[40] = GetProcAddress(sdl2Handle, "SDL_CreateRGBSurfaceWithFormat");
	sdl2Table[41] = GetProcAddress(sdl2Handle, "SDL_CreateRGBSurfaceWithFormatFrom");
	sdl2Table[42] = GetProcAddress(sdl2Handle, "SDL_CreateRenderer");
	sdl2Table[43] = GetProcAddress(sdl2Handle, "SDL_CreateSemaphore");
	sdl2Table[44] = GetProcAddress(sdl2Handle, "SDL_CreateShapedWindow");
	sdl2Table[45] = GetProcAddress(sdl2Handle, "SDL_CreateSoftwareRenderer");
	sdl2Table[46] = GetProcAddress(sdl2Handle, "SDL_CreateSystemCursor");
	sdl2Table[47] = GetProcAddress(sdl2Handle, "SDL_CreateTexture");
	sdl2Table[48] = GetProcAddress(sdl2Handle, "SDL_CreateTextureFromSurface");
	sdl2Table[49] = GetProcAddress(sdl2Handle, "SDL_CreateThread");
	sdl2Table[50] = GetProcAddress(sdl2Handle, "SDL_CreateWindow");
	sdl2Table[51] = GetProcAddress(sdl2Handle, "SDL_CreateWindowAndRenderer");
	sdl2Table[52] = GetProcAddress(sdl2Handle, "SDL_CreateWindowFrom");
	sdl2Table[53] = GetProcAddress(sdl2Handle, "SDL_DXGIGetOutputInfo");
	sdl2Table[54] = GetProcAddress(sdl2Handle, "SDL_DYNAPI_entry");
	sdl2Table[55] = GetProcAddress(sdl2Handle, "SDL_DelEventWatch");
	sdl2Table[56] = GetProcAddress(sdl2Handle, "SDL_DelHintCallback");
	sdl2Table[57] = GetProcAddress(sdl2Handle, "SDL_Delay");
	sdl2Table[58] = GetProcAddress(sdl2Handle, "SDL_DequeueAudio");
	sdl2Table[59] = GetProcAddress(sdl2Handle, "SDL_DestroyCond");
	sdl2Table[60] = GetProcAddress(sdl2Handle, "SDL_DestroyMutex");
	sdl2Table[61] = GetProcAddress(sdl2Handle, "SDL_DestroyRenderer");
	sdl2Table[62] = GetProcAddress(sdl2Handle, "SDL_DestroySemaphore");
	sdl2Table[63] = GetProcAddress(sdl2Handle, "SDL_DestroyTexture");
	sdl2Table[64] = GetProcAddress(sdl2Handle, "SDL_DestroyWindow");
	sdl2Table[65] = GetProcAddress(sdl2Handle, "SDL_DetachThread");
	sdl2Table[66] = GetProcAddress(sdl2Handle, "SDL_Direct3D9GetAdapterIndex");
	sdl2Table[67] = GetProcAddress(sdl2Handle, "SDL_DisableScreenSaver");
	sdl2Table[68] = GetProcAddress(sdl2Handle, "SDL_EnableScreenSaver");
	sdl2Table[69] = GetProcAddress(sdl2Handle, "SDL_EnclosePoints");
	sdl2Table[70] = GetProcAddress(sdl2Handle, "SDL_Error");
	sdl2Table[71] = GetProcAddress(sdl2Handle, "SDL_EventState");
	sdl2Table[72] = GetProcAddress(sdl2Handle, "SDL_FillRect");
	sdl2Table[73] = GetProcAddress(sdl2Handle, "SDL_FillRects");
	sdl2Table[74] = GetProcAddress(sdl2Handle, "SDL_FilterEvents");
	sdl2Table[75] = GetProcAddress(sdl2Handle, "SDL_FlushEvent");
	sdl2Table[76] = GetProcAddress(sdl2Handle, "SDL_FlushEvents");
	sdl2Table[77] = GetProcAddress(sdl2Handle, "SDL_FreeCursor");
	sdl2Table[78] = GetProcAddress(sdl2Handle, "SDL_FreeFormat");
	sdl2Table[79] = GetProcAddress(sdl2Handle, "SDL_FreePalette");
	sdl2Table[80] = GetProcAddress(sdl2Handle, "SDL_FreeRW");
	sdl2Table[81] = GetProcAddress(sdl2Handle, "SDL_FreeSurface");
	sdl2Table[82] = GetProcAddress(sdl2Handle, "SDL_FreeWAV");
	sdl2Table[83] = GetProcAddress(sdl2Handle, "SDL_GL_BindTexture");
	sdl2Table[84] = GetProcAddress(sdl2Handle, "SDL_GL_CreateContext");
	sdl2Table[85] = GetProcAddress(sdl2Handle, "SDL_GL_DeleteContext");
	sdl2Table[86] = GetProcAddress(sdl2Handle, "SDL_GL_ExtensionSupported");
	sdl2Table[87] = GetProcAddress(sdl2Handle, "SDL_GL_GetAttribute");
	sdl2Table[88] = GetProcAddress(sdl2Handle, "SDL_GL_GetCurrentContext");
	sdl2Table[89] = GetProcAddress(sdl2Handle, "SDL_GL_GetCurrentWindow");
	sdl2Table[90] = GetProcAddress(sdl2Handle, "SDL_GL_GetDrawableSize");
	sdl2Table[91] = GetProcAddress(sdl2Handle, "SDL_GL_GetProcAddress");
	sdl2Table[92] = GetProcAddress(sdl2Handle, "SDL_GL_GetSwapInterval");
	sdl2Table[93] = GetProcAddress(sdl2Handle, "SDL_GL_LoadLibrary");
	sdl2Table[94] = GetProcAddress(sdl2Handle, "SDL_GL_MakeCurrent");
	sdl2Table[95] = GetProcAddress(sdl2Handle, "SDL_GL_ResetAttributes");
	sdl2Table[96] = GetProcAddress(sdl2Handle, "SDL_GL_SetAttribute");
	sdl2Table[97] = GetProcAddress(sdl2Handle, "SDL_GL_SetSwapInterval");
	sdl2Table[98] = GetProcAddress(sdl2Handle, "SDL_GL_SwapWindow");
	sdl2Table[99] = GetProcAddress(sdl2Handle, "SDL_GL_UnbindTexture");
	sdl2Table[100] = GetProcAddress(sdl2Handle, "SDL_GL_UnloadLibrary");
	sdl2Table[101] = GetProcAddress(sdl2Handle, "SDL_GameControllerAddMapping");
	sdl2Table[102] = GetProcAddress(sdl2Handle, "SDL_GameControllerAddMappingsFromRW");
	sdl2Table[103] = GetProcAddress(sdl2Handle, "SDL_GameControllerClose");
	sdl2Table[104] = GetProcAddress(sdl2Handle, "SDL_GameControllerEventState");
	sdl2Table[105] = GetProcAddress(sdl2Handle, "SDL_GameControllerFromInstanceID");
	sdl2Table[106] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetAttached");
	sdl2Table[107] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetAxis");
	sdl2Table[108] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetAxisFromString");
	sdl2Table[109] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetBindForAxis");
	sdl2Table[110] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetBindForButton");
	sdl2Table[111] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetButton");
	sdl2Table[112] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetButtonFromString");
	sdl2Table[113] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetJoystick");
	sdl2Table[114] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetStringForAxis");
	sdl2Table[115] = GetProcAddress(sdl2Handle, "SDL_GameControllerGetStringForButton");
	sdl2Table[116] = GetProcAddress(sdl2Handle, "SDL_GameControllerMapping");
	sdl2Table[117] = GetProcAddress(sdl2Handle, "SDL_GameControllerMappingForGUID");
	sdl2Table[118] = GetProcAddress(sdl2Handle, "SDL_GameControllerName");
	sdl2Table[119] = GetProcAddress(sdl2Handle, "SDL_GameControllerNameForIndex");
	sdl2Table[120] = GetProcAddress(sdl2Handle, "SDL_GameControllerOpen");
	sdl2Table[121] = GetProcAddress(sdl2Handle, "SDL_GameControllerUpdate");
	sdl2Table[122] = GetProcAddress(sdl2Handle, "SDL_GetAssertionHandler");
	sdl2Table[123] = GetProcAddress(sdl2Handle, "SDL_GetAssertionReport");
	sdl2Table[124] = GetProcAddress(sdl2Handle, "SDL_GetAudioDeviceName");
	sdl2Table[125] = GetProcAddress(sdl2Handle, "SDL_GetAudioDeviceStatus");
	sdl2Table[126] = GetProcAddress(sdl2Handle, "SDL_GetAudioDriver");
	sdl2Table[127] = GetProcAddress(sdl2Handle, "SDL_GetAudioStatus");
	sdl2Table[128] = GetProcAddress(sdl2Handle, "SDL_GetBasePath");
	sdl2Table[129] = GetProcAddress(sdl2Handle, "SDL_GetCPUCacheLineSize");
	sdl2Table[130] = GetProcAddress(sdl2Handle, "SDL_GetCPUCount");
	sdl2Table[131] = GetProcAddress(sdl2Handle, "SDL_GetClipRect");
	sdl2Table[132] = GetProcAddress(sdl2Handle, "SDL_GetClipboardText");
	sdl2Table[133] = GetProcAddress(sdl2Handle, "SDL_GetClosestDisplayMode");
	sdl2Table[134] = GetProcAddress(sdl2Handle, "SDL_GetColorKey");
	sdl2Table[135] = GetProcAddress(sdl2Handle, "SDL_GetCurrentAudioDriver");
	sdl2Table[136] = GetProcAddress(sdl2Handle, "SDL_GetCurrentDisplayMode");
	sdl2Table[137] = GetProcAddress(sdl2Handle, "SDL_GetCurrentVideoDriver");
	sdl2Table[138] = GetProcAddress(sdl2Handle, "SDL_GetCursor");
	sdl2Table[139] = GetProcAddress(sdl2Handle, "SDL_GetDefaultAssertionHandler");
	sdl2Table[140] = GetProcAddress(sdl2Handle, "SDL_GetDefaultCursor");
	sdl2Table[141] = GetProcAddress(sdl2Handle, "SDL_GetDesktopDisplayMode");
	sdl2Table[142] = GetProcAddress(sdl2Handle, "SDL_GetDisplayBounds");
	sdl2Table[143] = GetProcAddress(sdl2Handle, "SDL_GetDisplayDPI");
	sdl2Table[144] = GetProcAddress(sdl2Handle, "SDL_GetDisplayMode");
	sdl2Table[145] = GetProcAddress(sdl2Handle, "SDL_GetDisplayName");
	sdl2Table[146] = GetProcAddress(sdl2Handle, "SDL_GetDisplayUsableBounds");
	sdl2Table[147] = GetProcAddress(sdl2Handle, "SDL_GetError");
	sdl2Table[148] = GetProcAddress(sdl2Handle, "SDL_GetEventFilter");
	sdl2Table[149] = GetProcAddress(sdl2Handle, "SDL_GetGlobalMouseState");
	sdl2Table[150] = GetProcAddress(sdl2Handle, "SDL_GetGrabbedWindow");
	sdl2Table[151] = GetProcAddress(sdl2Handle, "SDL_GetHint");
	sdl2Table[152] = GetProcAddress(sdl2Handle, "SDL_GetHintBoolean");
	sdl2Table[153] = GetProcAddress(sdl2Handle, "SDL_GetKeyFromName");
	sdl2Table[154] = GetProcAddress(sdl2Handle, "SDL_GetKeyFromScancode");
	sdl2Table[155] = GetProcAddress(sdl2Handle, "SDL_GetKeyName");
	sdl2Table[156] = GetProcAddress(sdl2Handle, "SDL_GetKeyboardFocus");
	sdl2Table[157] = GetProcAddress(sdl2Handle, "SDL_GetKeyboardState");
	sdl2Table[158] = GetProcAddress(sdl2Handle, "SDL_GetModState");
	sdl2Table[159] = GetProcAddress(sdl2Handle, "SDL_GetMouseFocus");
	sdl2Table[160] = GetProcAddress(sdl2Handle, "SDL_GetMouseState");
	sdl2Table[161] = GetProcAddress(sdl2Handle, "SDL_GetNumAudioDevices");
	sdl2Table[162] = GetProcAddress(sdl2Handle, "SDL_GetNumAudioDrivers");
	sdl2Table[163] = GetProcAddress(sdl2Handle, "SDL_GetNumDisplayModes");
	sdl2Table[164] = GetProcAddress(sdl2Handle, "SDL_GetNumRenderDrivers");
	sdl2Table[165] = GetProcAddress(sdl2Handle, "SDL_GetNumTouchDevices");
	sdl2Table[166] = GetProcAddress(sdl2Handle, "SDL_GetNumTouchFingers");
	sdl2Table[167] = GetProcAddress(sdl2Handle, "SDL_GetNumVideoDisplays");
	sdl2Table[168] = GetProcAddress(sdl2Handle, "SDL_GetNumVideoDrivers");
	sdl2Table[169] = GetProcAddress(sdl2Handle, "SDL_GetPerformanceCounter");
	sdl2Table[170] = GetProcAddress(sdl2Handle, "SDL_GetPerformanceFrequency");
	sdl2Table[171] = GetProcAddress(sdl2Handle, "SDL_GetPixelFormatName");
	sdl2Table[172] = GetProcAddress(sdl2Handle, "SDL_GetPlatform");
	sdl2Table[173] = GetProcAddress(sdl2Handle, "SDL_GetPowerInfo");
	sdl2Table[174] = GetProcAddress(sdl2Handle, "SDL_GetPrefPath");
	sdl2Table[175] = GetProcAddress(sdl2Handle, "SDL_GetQueuedAudioSize");
	sdl2Table[176] = GetProcAddress(sdl2Handle, "SDL_GetRGB");
	sdl2Table[177] = GetProcAddress(sdl2Handle, "SDL_GetRGBA");
	sdl2Table[178] = GetProcAddress(sdl2Handle, "SDL_GetRelativeMouseMode");
	sdl2Table[179] = GetProcAddress(sdl2Handle, "SDL_GetRelativeMouseState");
	sdl2Table[180] = GetProcAddress(sdl2Handle, "SDL_GetRenderDrawBlendMode");
	sdl2Table[181] = GetProcAddress(sdl2Handle, "SDL_GetRenderDrawColor");
	sdl2Table[182] = GetProcAddress(sdl2Handle, "SDL_GetRenderDriverInfo");
	sdl2Table[183] = GetProcAddress(sdl2Handle, "SDL_GetRenderTarget");
	sdl2Table[184] = GetProcAddress(sdl2Handle, "SDL_GetRenderer");
	sdl2Table[185] = GetProcAddress(sdl2Handle, "SDL_GetRendererInfo");
	sdl2Table[186] = GetProcAddress(sdl2Handle, "SDL_GetRendererOutputSize");
	sdl2Table[187] = GetProcAddress(sdl2Handle, "SDL_GetRevision");
	sdl2Table[188] = GetProcAddress(sdl2Handle, "SDL_GetRevisionNumber");
	sdl2Table[189] = GetProcAddress(sdl2Handle, "SDL_GetScancodeFromKey");
	sdl2Table[190] = GetProcAddress(sdl2Handle, "SDL_GetScancodeFromName");
	sdl2Table[191] = GetProcAddress(sdl2Handle, "SDL_GetScancodeName");
	sdl2Table[192] = GetProcAddress(sdl2Handle, "SDL_GetShapedWindowMode");
	sdl2Table[193] = GetProcAddress(sdl2Handle, "SDL_GetSurfaceAlphaMod");
	sdl2Table[194] = GetProcAddress(sdl2Handle, "SDL_GetSurfaceBlendMode");
	sdl2Table[195] = GetProcAddress(sdl2Handle, "SDL_GetSurfaceColorMod");
	sdl2Table[196] = GetProcAddress(sdl2Handle, "SDL_GetSystemRAM");
	sdl2Table[197] = GetProcAddress(sdl2Handle, "SDL_GetTextureAlphaMod");
	sdl2Table[198] = GetProcAddress(sdl2Handle, "SDL_GetTextureBlendMode");
	sdl2Table[199] = GetProcAddress(sdl2Handle, "SDL_GetTextureColorMod");
	sdl2Table[200] = GetProcAddress(sdl2Handle, "SDL_GetThreadID");
	sdl2Table[201] = GetProcAddress(sdl2Handle, "SDL_GetThreadName");
	sdl2Table[202] = GetProcAddress(sdl2Handle, "SDL_GetTicks");
	sdl2Table[203] = GetProcAddress(sdl2Handle, "SDL_GetTouchDevice");
	sdl2Table[204] = GetProcAddress(sdl2Handle, "SDL_GetTouchFinger");
	sdl2Table[205] = GetProcAddress(sdl2Handle, "SDL_GetVersion");
	sdl2Table[206] = GetProcAddress(sdl2Handle, "SDL_GetVideoDriver");
	sdl2Table[207] = GetProcAddress(sdl2Handle, "SDL_GetWindowBordersSize");
	sdl2Table[208] = GetProcAddress(sdl2Handle, "SDL_GetWindowBrightness");
	sdl2Table[209] = GetProcAddress(sdl2Handle, "SDL_GetWindowData");
	sdl2Table[210] = GetProcAddress(sdl2Handle, "SDL_GetWindowDisplayIndex");
	sdl2Table[211] = GetProcAddress(sdl2Handle, "SDL_GetWindowDisplayMode");
	sdl2Table[212] = GetProcAddress(sdl2Handle, "SDL_GetWindowFlags");
	sdl2Table[213] = GetProcAddress(sdl2Handle, "SDL_GetWindowFromID");
	sdl2Table[214] = GetProcAddress(sdl2Handle, "SDL_GetWindowGammaRamp");
	sdl2Table[215] = GetProcAddress(sdl2Handle, "SDL_GetWindowGrab");
	sdl2Table[216] = GetProcAddress(sdl2Handle, "SDL_GetWindowID");
	sdl2Table[217] = GetProcAddress(sdl2Handle, "SDL_GetWindowMaximumSize");
	sdl2Table[218] = GetProcAddress(sdl2Handle, "SDL_GetWindowMinimumSize");
	sdl2Table[219] = GetProcAddress(sdl2Handle, "SDL_GetWindowOpacity");
	sdl2Table[220] = GetProcAddress(sdl2Handle, "SDL_GetWindowPixelFormat");
	sdl2Table[221] = GetProcAddress(sdl2Handle, "SDL_GetWindowPosition");
	sdl2Table[222] = GetProcAddress(sdl2Handle, "SDL_GetWindowSize");
	sdl2Table[223] = GetProcAddress(sdl2Handle, "SDL_GetWindowSurface");
	sdl2Table[224] = GetProcAddress(sdl2Handle, "SDL_GetWindowTitle");
	sdl2Table[225] = GetProcAddress(sdl2Handle, "SDL_GetWindowWMInfo");
	sdl2Table[226] = GetProcAddress(sdl2Handle, "SDL_HapticClose");
	sdl2Table[227] = GetProcAddress(sdl2Handle, "SDL_HapticDestroyEffect");
	sdl2Table[228] = GetProcAddress(sdl2Handle, "SDL_HapticEffectSupported");
	sdl2Table[229] = GetProcAddress(sdl2Handle, "SDL_HapticGetEffectStatus");
	sdl2Table[230] = GetProcAddress(sdl2Handle, "SDL_HapticIndex");
	sdl2Table[231] = GetProcAddress(sdl2Handle, "SDL_HapticName");
	sdl2Table[232] = GetProcAddress(sdl2Handle, "SDL_HapticNewEffect");
	sdl2Table[233] = GetProcAddress(sdl2Handle, "SDL_HapticNumAxes");
	sdl2Table[234] = GetProcAddress(sdl2Handle, "SDL_HapticNumEffects");
	sdl2Table[235] = GetProcAddress(sdl2Handle, "SDL_HapticNumEffectsPlaying");
	sdl2Table[236] = GetProcAddress(sdl2Handle, "SDL_HapticOpen");
	sdl2Table[237] = GetProcAddress(sdl2Handle, "SDL_HapticOpenFromJoystick");
	sdl2Table[238] = GetProcAddress(sdl2Handle, "SDL_HapticOpenFromMouse");
	sdl2Table[239] = GetProcAddress(sdl2Handle, "SDL_HapticOpened");
	sdl2Table[240] = GetProcAddress(sdl2Handle, "SDL_HapticPause");
	sdl2Table[241] = GetProcAddress(sdl2Handle, "SDL_HapticQuery");
	sdl2Table[242] = GetProcAddress(sdl2Handle, "SDL_HapticRumbleInit");
	sdl2Table[243] = GetProcAddress(sdl2Handle, "SDL_HapticRumblePlay");
	sdl2Table[244] = GetProcAddress(sdl2Handle, "SDL_HapticRumbleStop");
	sdl2Table[245] = GetProcAddress(sdl2Handle, "SDL_HapticRumbleSupported");
	sdl2Table[246] = GetProcAddress(sdl2Handle, "SDL_HapticRunEffect");
	sdl2Table[247] = GetProcAddress(sdl2Handle, "SDL_HapticSetAutocenter");
	sdl2Table[248] = GetProcAddress(sdl2Handle, "SDL_HapticSetGain");
	sdl2Table[249] = GetProcAddress(sdl2Handle, "SDL_HapticStopAll");
	sdl2Table[250] = GetProcAddress(sdl2Handle, "SDL_HapticStopEffect");
	sdl2Table[251] = GetProcAddress(sdl2Handle, "SDL_HapticUnpause");
	sdl2Table[252] = GetProcAddress(sdl2Handle, "SDL_HapticUpdateEffect");
	sdl2Table[253] = GetProcAddress(sdl2Handle, "SDL_Has3DNow");
	sdl2Table[254] = GetProcAddress(sdl2Handle, "SDL_HasAVX");
	sdl2Table[255] = GetProcAddress(sdl2Handle, "SDL_HasAVX2");
	sdl2Table[256] = GetProcAddress(sdl2Handle, "SDL_HasAltiVec");
	sdl2Table[257] = GetProcAddress(sdl2Handle, "SDL_HasClipboardText");
	sdl2Table[258] = GetProcAddress(sdl2Handle, "SDL_HasEvent");
	sdl2Table[259] = GetProcAddress(sdl2Handle, "SDL_HasEvents");
	sdl2Table[260] = GetProcAddress(sdl2Handle, "SDL_HasIntersection");
	sdl2Table[261] = GetProcAddress(sdl2Handle, "SDL_HasMMX");
	sdl2Table[262] = GetProcAddress(sdl2Handle, "SDL_HasRDTSC");
	sdl2Table[263] = GetProcAddress(sdl2Handle, "SDL_HasSSE");
	sdl2Table[264] = GetProcAddress(sdl2Handle, "SDL_HasSSE2");
	sdl2Table[265] = GetProcAddress(sdl2Handle, "SDL_HasSSE3");
	sdl2Table[266] = GetProcAddress(sdl2Handle, "SDL_HasSSE41");
	sdl2Table[267] = GetProcAddress(sdl2Handle, "SDL_HasSSE42");
	sdl2Table[268] = GetProcAddress(sdl2Handle, "SDL_HasScreenKeyboardSupport");
	sdl2Table[269] = GetProcAddress(sdl2Handle, "SDL_HideWindow");
	sdl2Table[270] = GetProcAddress(sdl2Handle, "SDL_Init");
	sdl2Table[271] = GetProcAddress(sdl2Handle, "SDL_InitSubSystem");
	sdl2Table[272] = GetProcAddress(sdl2Handle, "SDL_IntersectRect");
	sdl2Table[273] = GetProcAddress(sdl2Handle, "SDL_IntersectRectAndLine");
	sdl2Table[274] = GetProcAddress(sdl2Handle, "SDL_IsGameController");
	sdl2Table[275] = GetProcAddress(sdl2Handle, "SDL_IsScreenKeyboardShown");
	sdl2Table[276] = GetProcAddress(sdl2Handle, "SDL_IsScreenSaverEnabled");
	sdl2Table[277] = GetProcAddress(sdl2Handle, "SDL_IsShapedWindow");
	sdl2Table[278] = GetProcAddress(sdl2Handle, "SDL_IsTextInputActive");
	sdl2Table[279] = GetProcAddress(sdl2Handle, "SDL_JoystickClose");
	sdl2Table[280] = GetProcAddress(sdl2Handle, "SDL_JoystickCurrentPowerLevel");
	sdl2Table[281] = GetProcAddress(sdl2Handle, "SDL_JoystickEventState");
	sdl2Table[282] = GetProcAddress(sdl2Handle, "SDL_JoystickFromInstanceID");
	sdl2Table[283] = GetProcAddress(sdl2Handle, "SDL_JoystickGetAttached");
	sdl2Table[284] = GetProcAddress(sdl2Handle, "SDL_JoystickGetAxis");
	sdl2Table[285] = GetProcAddress(sdl2Handle, "SDL_JoystickGetBall");
	sdl2Table[286] = GetProcAddress(sdl2Handle, "SDL_JoystickGetButton");
	sdl2Table[287] = GetProcAddress(sdl2Handle, "SDL_JoystickGetDeviceGUID");
	sdl2Table[288] = GetProcAddress(sdl2Handle, "SDL_JoystickGetGUID");
	sdl2Table[289] = GetProcAddress(sdl2Handle, "SDL_JoystickGetGUIDFromString");
	sdl2Table[290] = GetProcAddress(sdl2Handle, "SDL_JoystickGetGUIDString");
	sdl2Table[291] = GetProcAddress(sdl2Handle, "SDL_JoystickGetHat");
	sdl2Table[292] = GetProcAddress(sdl2Handle, "SDL_JoystickInstanceID");
	sdl2Table[293] = GetProcAddress(sdl2Handle, "SDL_JoystickIsHaptic");
	sdl2Table[294] = GetProcAddress(sdl2Handle, "SDL_JoystickName");
	sdl2Table[295] = GetProcAddress(sdl2Handle, "SDL_JoystickNameForIndex");
	sdl2Table[296] = GetProcAddress(sdl2Handle, "SDL_JoystickNumAxes");
	sdl2Table[297] = GetProcAddress(sdl2Handle, "SDL_JoystickNumBalls");
	sdl2Table[298] = GetProcAddress(sdl2Handle, "SDL_JoystickNumButtons");
	sdl2Table[299] = GetProcAddress(sdl2Handle, "SDL_JoystickNumHats");
	sdl2Table[300] = GetProcAddress(sdl2Handle, "SDL_JoystickOpen");
	sdl2Table[301] = GetProcAddress(sdl2Handle, "SDL_JoystickUpdate");
	sdl2Table[302] = GetProcAddress(sdl2Handle, "SDL_LoadBMP_RW");
	sdl2Table[303] = GetProcAddress(sdl2Handle, "SDL_LoadDollarTemplates");
	sdl2Table[304] = GetProcAddress(sdl2Handle, "SDL_LoadFunction");
	sdl2Table[305] = GetProcAddress(sdl2Handle, "SDL_LoadObject");
	sdl2Table[306] = GetProcAddress(sdl2Handle, "SDL_LoadWAV_RW");
	sdl2Table[307] = GetProcAddress(sdl2Handle, "SDL_LockAudio");
	sdl2Table[308] = GetProcAddress(sdl2Handle, "SDL_LockAudioDevice");
	sdl2Table[309] = GetProcAddress(sdl2Handle, "SDL_LockMutex");
	sdl2Table[310] = GetProcAddress(sdl2Handle, "SDL_LockSurface");
	sdl2Table[311] = GetProcAddress(sdl2Handle, "SDL_LockTexture");
	sdl2Table[312] = GetProcAddress(sdl2Handle, "SDL_Log");
	sdl2Table[313] = GetProcAddress(sdl2Handle, "SDL_LogCritical");
	sdl2Table[314] = GetProcAddress(sdl2Handle, "SDL_LogDebug");
	sdl2Table[315] = GetProcAddress(sdl2Handle, "SDL_LogError");
	sdl2Table[316] = GetProcAddress(sdl2Handle, "SDL_LogGetOutputFunction");
	sdl2Table[317] = GetProcAddress(sdl2Handle, "SDL_LogGetPriority");
	sdl2Table[318] = GetProcAddress(sdl2Handle, "SDL_LogInfo");
	sdl2Table[319] = GetProcAddress(sdl2Handle, "SDL_LogMessage");
	sdl2Table[320] = GetProcAddress(sdl2Handle, "SDL_LogMessageV");
	sdl2Table[321] = GetProcAddress(sdl2Handle, "SDL_LogResetPriorities");
	sdl2Table[322] = GetProcAddress(sdl2Handle, "SDL_LogSetAllPriority");
	sdl2Table[323] = GetProcAddress(sdl2Handle, "SDL_LogSetOutputFunction");
	sdl2Table[324] = GetProcAddress(sdl2Handle, "SDL_LogSetPriority");
	sdl2Table[325] = GetProcAddress(sdl2Handle, "SDL_LogVerbose");
	sdl2Table[326] = GetProcAddress(sdl2Handle, "SDL_LogWarn");
	sdl2Table[327] = GetProcAddress(sdl2Handle, "SDL_LowerBlit");
	sdl2Table[328] = GetProcAddress(sdl2Handle, "SDL_LowerBlitScaled");
	sdl2Table[329] = GetProcAddress(sdl2Handle, "SDL_MapRGB");
	sdl2Table[330] = GetProcAddress(sdl2Handle, "SDL_MapRGBA");
	sdl2Table[331] = GetProcAddress(sdl2Handle, "SDL_MasksToPixelFormatEnum");
	sdl2Table[332] = GetProcAddress(sdl2Handle, "SDL_MaximizeWindow");
	sdl2Table[333] = GetProcAddress(sdl2Handle, "SDL_MinimizeWindow");
	sdl2Table[334] = GetProcAddress(sdl2Handle, "SDL_MixAudio");
	sdl2Table[335] = GetProcAddress(sdl2Handle, "SDL_MixAudioFormat");
	sdl2Table[336] = GetProcAddress(sdl2Handle, "SDL_MouseIsHaptic");
	sdl2Table[337] = GetProcAddress(sdl2Handle, "SDL_NumHaptics");
	sdl2Table[338] = GetProcAddress(sdl2Handle, "SDL_NumJoysticks");
	sdl2Table[339] = GetProcAddress(sdl2Handle, "SDL_OpenAudio");
	sdl2Table[340] = GetProcAddress(sdl2Handle, "SDL_OpenAudioDevice");
	sdl2Table[341] = GetProcAddress(sdl2Handle, "SDL_PauseAudio");
	sdl2Table[342] = GetProcAddress(sdl2Handle, "SDL_PauseAudioDevice");
	sdl2Table[343] = GetProcAddress(sdl2Handle, "SDL_PeepEvents");
	sdl2Table[344] = GetProcAddress(sdl2Handle, "SDL_PixelFormatEnumToMasks");
	sdl2Table[345] = GetProcAddress(sdl2Handle, "SDL_PollEvent");
	sdl2Table[346] = GetProcAddress(sdl2Handle, "SDL_PumpEvents");
	sdl2Table[347] = GetProcAddress(sdl2Handle, "SDL_PushEvent");
	sdl2Table[348] = GetProcAddress(sdl2Handle, "SDL_QueryTexture");
	sdl2Table[349] = GetProcAddress(sdl2Handle, "SDL_QueueAudio");
	sdl2Table[350] = GetProcAddress(sdl2Handle, "SDL_Quit");
	sdl2Table[351] = GetProcAddress(sdl2Handle, "SDL_QuitSubSystem");
	sdl2Table[352] = GetProcAddress(sdl2Handle, "SDL_RWFromConstMem");
	sdl2Table[353] = GetProcAddress(sdl2Handle, "SDL_RWFromFP");
	sdl2Table[354] = GetProcAddress(sdl2Handle, "SDL_RWFromFile");
	sdl2Table[355] = GetProcAddress(sdl2Handle, "SDL_RWFromMem");
	sdl2Table[356] = GetProcAddress(sdl2Handle, "SDL_RaiseWindow");
	sdl2Table[357] = GetProcAddress(sdl2Handle, "SDL_ReadBE16");
	sdl2Table[358] = GetProcAddress(sdl2Handle, "SDL_ReadBE32");
	sdl2Table[359] = GetProcAddress(sdl2Handle, "SDL_ReadBE64");
	sdl2Table[360] = GetProcAddress(sdl2Handle, "SDL_ReadLE16");
	sdl2Table[361] = GetProcAddress(sdl2Handle, "SDL_ReadLE32");
	sdl2Table[362] = GetProcAddress(sdl2Handle, "SDL_ReadLE64");
	sdl2Table[363] = GetProcAddress(sdl2Handle, "SDL_ReadU8");
	sdl2Table[364] = GetProcAddress(sdl2Handle, "SDL_RecordGesture");
	sdl2Table[365] = GetProcAddress(sdl2Handle, "SDL_RegisterApp");
	sdl2Table[366] = GetProcAddress(sdl2Handle, "SDL_RegisterEvents");
	sdl2Table[367] = GetProcAddress(sdl2Handle, "SDL_RemoveTimer");
	sdl2Table[368] = GetProcAddress(sdl2Handle, "SDL_RenderClear");
	sdl2Table[369] = GetProcAddress(sdl2Handle, "SDL_RenderCopy");
	sdl2Table[370] = GetProcAddress(sdl2Handle, "SDL_RenderCopyEx");
	sdl2Table[371] = GetProcAddress(sdl2Handle, "SDL_RenderDrawLine");
	sdl2Table[372] = GetProcAddress(sdl2Handle, "SDL_RenderDrawLines");
	sdl2Table[373] = GetProcAddress(sdl2Handle, "SDL_RenderDrawPoint");
	sdl2Table[374] = GetProcAddress(sdl2Handle, "SDL_RenderDrawPoints");
	sdl2Table[375] = GetProcAddress(sdl2Handle, "SDL_RenderDrawRect");
	sdl2Table[376] = GetProcAddress(sdl2Handle, "SDL_RenderDrawRects");
	sdl2Table[377] = GetProcAddress(sdl2Handle, "SDL_RenderFillRect");
	sdl2Table[378] = GetProcAddress(sdl2Handle, "SDL_RenderFillRects");
	sdl2Table[379] = GetProcAddress(sdl2Handle, "SDL_RenderGetClipRect");
	sdl2Table[380] = GetProcAddress(sdl2Handle, "SDL_RenderGetD3D9Device");
	sdl2Table[381] = GetProcAddress(sdl2Handle, "SDL_RenderGetIntegerScale");
	sdl2Table[382] = GetProcAddress(sdl2Handle, "SDL_RenderGetLogicalSize");
	sdl2Table[383] = GetProcAddress(sdl2Handle, "SDL_RenderGetScale");
	sdl2Table[384] = GetProcAddress(sdl2Handle, "SDL_RenderGetViewport");
	sdl2Table[385] = GetProcAddress(sdl2Handle, "SDL_RenderIsClipEnabled");
	sdl2Table[386] = GetProcAddress(sdl2Handle, "SDL_RenderPresent");
	sdl2Table[387] = GetProcAddress(sdl2Handle, "SDL_RenderReadPixels");
	sdl2Table[388] = GetProcAddress(sdl2Handle, "SDL_RenderSetClipRect");
	sdl2Table[389] = GetProcAddress(sdl2Handle, "SDL_RenderSetIntegerScale");
	sdl2Table[390] = GetProcAddress(sdl2Handle, "SDL_RenderSetLogicalSize");
	sdl2Table[391] = GetProcAddress(sdl2Handle, "SDL_RenderSetScale");
	sdl2Table[392] = GetProcAddress(sdl2Handle, "SDL_RenderSetViewport");
	sdl2Table[393] = GetProcAddress(sdl2Handle, "SDL_RenderTargetSupported");
	sdl2Table[394] = GetProcAddress(sdl2Handle, "SDL_ReportAssertion");
	sdl2Table[395] = GetProcAddress(sdl2Handle, "SDL_ResetAssertionReport");
	sdl2Table[396] = GetProcAddress(sdl2Handle, "SDL_RestoreWindow");
	sdl2Table[397] = GetProcAddress(sdl2Handle, "SDL_SaveAllDollarTemplates");
	sdl2Table[398] = GetProcAddress(sdl2Handle, "SDL_SaveBMP_RW");
	sdl2Table[399] = GetProcAddress(sdl2Handle, "SDL_SaveDollarTemplate");
	sdl2Table[400] = GetProcAddress(sdl2Handle, "SDL_SemPost");
	sdl2Table[401] = GetProcAddress(sdl2Handle, "SDL_SemTryWait");
	sdl2Table[402] = GetProcAddress(sdl2Handle, "SDL_SemValue");
	sdl2Table[403] = GetProcAddress(sdl2Handle, "SDL_SemWait");
	sdl2Table[404] = GetProcAddress(sdl2Handle, "SDL_SemWaitTimeout");
	sdl2Table[405] = GetProcAddress(sdl2Handle, "SDL_SetAssertionHandler");
	sdl2Table[406] = GetProcAddress(sdl2Handle, "SDL_SetClipRect");
	sdl2Table[407] = GetProcAddress(sdl2Handle, "SDL_SetClipboardText");
	sdl2Table[408] = GetProcAddress(sdl2Handle, "SDL_SetColorKey");
	sdl2Table[409] = GetProcAddress(sdl2Handle, "SDL_SetCursor");
	sdl2Table[410] = GetProcAddress(sdl2Handle, "SDL_SetError");
	sdl2Table[411] = GetProcAddress(sdl2Handle, "SDL_SetEventFilter");
	sdl2Table[412] = GetProcAddress(sdl2Handle, "SDL_SetHint");
	sdl2Table[413] = GetProcAddress(sdl2Handle, "SDL_SetHintWithPriority");
	sdl2Table[414] = GetProcAddress(sdl2Handle, "SDL_SetMainReady");
	sdl2Table[415] = GetProcAddress(sdl2Handle, "SDL_SetModState");
	sdl2Table[416] = GetProcAddress(sdl2Handle, "SDL_SetPaletteColors");
	sdl2Table[417] = GetProcAddress(sdl2Handle, "SDL_SetPixelFormatPalette");
	sdl2Table[418] = GetProcAddress(sdl2Handle, "SDL_SetRelativeMouseMode");
	sdl2Table[419] = GetProcAddress(sdl2Handle, "SDL_SetRenderDrawBlendMode");
	sdl2Table[420] = GetProcAddress(sdl2Handle, "SDL_SetRenderDrawColor");
	sdl2Table[421] = GetProcAddress(sdl2Handle, "SDL_SetRenderTarget");
	sdl2Table[422] = GetProcAddress(sdl2Handle, "SDL_SetSurfaceAlphaMod");
	sdl2Table[423] = GetProcAddress(sdl2Handle, "SDL_SetSurfaceBlendMode");
	sdl2Table[424] = GetProcAddress(sdl2Handle, "SDL_SetSurfaceColorMod");
	sdl2Table[425] = GetProcAddress(sdl2Handle, "SDL_SetSurfacePalette");
	sdl2Table[426] = GetProcAddress(sdl2Handle, "SDL_SetSurfaceRLE");
	sdl2Table[427] = GetProcAddress(sdl2Handle, "SDL_SetTextInputRect");
	sdl2Table[428] = GetProcAddress(sdl2Handle, "SDL_SetTextureAlphaMod");
	sdl2Table[429] = GetProcAddress(sdl2Handle, "SDL_SetTextureBlendMode");
	sdl2Table[430] = GetProcAddress(sdl2Handle, "SDL_SetTextureColorMod");
	sdl2Table[431] = GetProcAddress(sdl2Handle, "SDL_SetThreadPriority");
	sdl2Table[432] = GetProcAddress(sdl2Handle, "SDL_SetWindowBordered");
	sdl2Table[433] = GetProcAddress(sdl2Handle, "SDL_SetWindowBrightness");
	sdl2Table[434] = GetProcAddress(sdl2Handle, "SDL_SetWindowData");
	sdl2Table[435] = GetProcAddress(sdl2Handle, "SDL_SetWindowDisplayMode");
	sdl2Table[436] = GetProcAddress(sdl2Handle, "SDL_SetWindowFullscreen");
	sdl2Table[437] = GetProcAddress(sdl2Handle, "SDL_SetWindowGammaRamp");
	sdl2Table[438] = GetProcAddress(sdl2Handle, "SDL_SetWindowGrab");
	sdl2Table[439] = GetProcAddress(sdl2Handle, "SDL_SetWindowHitTest");
	sdl2Table[440] = GetProcAddress(sdl2Handle, "SDL_SetWindowIcon");
	sdl2Table[441] = GetProcAddress(sdl2Handle, "SDL_SetWindowInputFocus");
	sdl2Table[442] = GetProcAddress(sdl2Handle, "SDL_SetWindowMaximumSize");
	sdl2Table[443] = GetProcAddress(sdl2Handle, "SDL_SetWindowMinimumSize");
	sdl2Table[444] = GetProcAddress(sdl2Handle, "SDL_SetWindowModalFor");
	sdl2Table[445] = GetProcAddress(sdl2Handle, "SDL_SetWindowOpacity");
	sdl2Table[446] = GetProcAddress(sdl2Handle, "SDL_SetWindowPosition");
	sdl2Table[447] = GetProcAddress(sdl2Handle, "SDL_SetWindowResizable");
	sdl2Table[448] = GetProcAddress(sdl2Handle, "SDL_SetWindowShape");
	sdl2Table[449] = GetProcAddress(sdl2Handle, "SDL_SetWindowSize");
	sdl2Table[450] = GetProcAddress(sdl2Handle, "SDL_SetWindowTitle");
	sdl2Table[451] = GetProcAddress(sdl2Handle, "SDL_SetWindowsMessageHook");
	sdl2Table[452] = GetProcAddress(sdl2Handle, "SDL_ShowCursor");
	sdl2Table[453] = GetProcAddress(sdl2Handle, "SDL_ShowMessageBox");
	sdl2Table[454] = GetProcAddress(sdl2Handle, "SDL_ShowSimpleMessageBox");
	sdl2Table[455] = GetProcAddress(sdl2Handle, "SDL_ShowWindow");
	sdl2Table[456] = GetProcAddress(sdl2Handle, "SDL_SoftStretch");
	sdl2Table[457] = GetProcAddress(sdl2Handle, "SDL_StartTextInput");
	sdl2Table[458] = GetProcAddress(sdl2Handle, "SDL_StopTextInput");
	sdl2Table[459] = GetProcAddress(sdl2Handle, "SDL_TLSCreate");
	sdl2Table[460] = GetProcAddress(sdl2Handle, "SDL_TLSGet");
	sdl2Table[461] = GetProcAddress(sdl2Handle, "SDL_TLSSet");
	sdl2Table[462] = GetProcAddress(sdl2Handle, "SDL_ThreadID");
	sdl2Table[463] = GetProcAddress(sdl2Handle, "SDL_TryLockMutex");
	sdl2Table[464] = GetProcAddress(sdl2Handle, "SDL_UnionRect");
	sdl2Table[465] = GetProcAddress(sdl2Handle, "SDL_UnloadObject");
	sdl2Table[466] = GetProcAddress(sdl2Handle, "SDL_UnlockAudio");
	sdl2Table[467] = GetProcAddress(sdl2Handle, "SDL_UnlockAudioDevice");
	sdl2Table[468] = GetProcAddress(sdl2Handle, "SDL_UnlockMutex");
	sdl2Table[469] = GetProcAddress(sdl2Handle, "SDL_UnlockSurface");
	sdl2Table[470] = GetProcAddress(sdl2Handle, "SDL_UnlockTexture");
	sdl2Table[471] = GetProcAddress(sdl2Handle, "SDL_UnregisterApp");
	sdl2Table[472] = GetProcAddress(sdl2Handle, "SDL_UpdateTexture");
	sdl2Table[473] = GetProcAddress(sdl2Handle, "SDL_UpdateWindowSurface");
	sdl2Table[474] = GetProcAddress(sdl2Handle, "SDL_UpdateWindowSurfaceRects");
	sdl2Table[475] = GetProcAddress(sdl2Handle, "SDL_UpdateYUVTexture");
	sdl2Table[476] = GetProcAddress(sdl2Handle, "SDL_UpperBlit");
	sdl2Table[477] = GetProcAddress(sdl2Handle, "SDL_UpperBlitScaled");
	sdl2Table[478] = GetProcAddress(sdl2Handle, "SDL_VideoInit");
	sdl2Table[479] = GetProcAddress(sdl2Handle, "SDL_VideoQuit");
	sdl2Table[480] = GetProcAddress(sdl2Handle, "SDL_WaitEvent");
	sdl2Table[481] = GetProcAddress(sdl2Handle, "SDL_WaitEventTimeout");
	sdl2Table[482] = GetProcAddress(sdl2Handle, "SDL_WaitThread");
	sdl2Table[483] = GetProcAddress(sdl2Handle, "SDL_WarpMouseGlobal");
	sdl2Table[484] = GetProcAddress(sdl2Handle, "SDL_WarpMouseInWindow");
	sdl2Table[485] = GetProcAddress(sdl2Handle, "SDL_WasInit");
	sdl2Table[486] = GetProcAddress(sdl2Handle, "SDL_WriteBE16");
	sdl2Table[487] = GetProcAddress(sdl2Handle, "SDL_WriteBE32");
	sdl2Table[488] = GetProcAddress(sdl2Handle, "SDL_WriteBE64");
	sdl2Table[489] = GetProcAddress(sdl2Handle, "SDL_WriteLE16");
	sdl2Table[490] = GetProcAddress(sdl2Handle, "SDL_WriteLE32");
	sdl2Table[491] = GetProcAddress(sdl2Handle, "SDL_WriteLE64");
	sdl2Table[492] = GetProcAddress(sdl2Handle, "SDL_WriteU8");
	sdl2Table[493] = GetProcAddress(sdl2Handle, "SDL_abs");
	sdl2Table[494] = GetProcAddress(sdl2Handle, "SDL_acos");
	sdl2Table[495] = GetProcAddress(sdl2Handle, "SDL_asin");
	sdl2Table[496] = GetProcAddress(sdl2Handle, "SDL_atan");
	sdl2Table[497] = GetProcAddress(sdl2Handle, "SDL_atan2");
	sdl2Table[498] = GetProcAddress(sdl2Handle, "SDL_atof");
	sdl2Table[499] = GetProcAddress(sdl2Handle, "SDL_atoi");
	sdl2Table[500] = GetProcAddress(sdl2Handle, "SDL_calloc");
	sdl2Table[501] = GetProcAddress(sdl2Handle, "SDL_ceil");
	sdl2Table[502] = GetProcAddress(sdl2Handle, "SDL_copysign");
	sdl2Table[503] = GetProcAddress(sdl2Handle, "SDL_cos");
	sdl2Table[504] = GetProcAddress(sdl2Handle, "SDL_cosf");
	sdl2Table[505] = GetProcAddress(sdl2Handle, "SDL_fabs");
	sdl2Table[506] = GetProcAddress(sdl2Handle, "SDL_floor");
	sdl2Table[507] = GetProcAddress(sdl2Handle, "SDL_free");
	sdl2Table[508] = GetProcAddress(sdl2Handle, "SDL_getenv");
	sdl2Table[509] = GetProcAddress(sdl2Handle, "SDL_iconv");
	sdl2Table[510] = GetProcAddress(sdl2Handle, "SDL_iconv_close");
	sdl2Table[511] = GetProcAddress(sdl2Handle, "SDL_iconv_open");
	sdl2Table[512] = GetProcAddress(sdl2Handle, "SDL_iconv_string");
	sdl2Table[513] = GetProcAddress(sdl2Handle, "SDL_isdigit");
	sdl2Table[514] = GetProcAddress(sdl2Handle, "SDL_isspace");
	sdl2Table[515] = GetProcAddress(sdl2Handle, "SDL_itoa");
	sdl2Table[516] = GetProcAddress(sdl2Handle, "SDL_lltoa");
	sdl2Table[517] = GetProcAddress(sdl2Handle, "SDL_log");
	sdl2Table[518] = GetProcAddress(sdl2Handle, "SDL_ltoa");
	sdl2Table[519] = GetProcAddress(sdl2Handle, "SDL_malloc");
	sdl2Table[520] = GetProcAddress(sdl2Handle, "SDL_memcmp");
	sdl2Table[521] = GetProcAddress(sdl2Handle, "SDL_memcpy");
	sdl2Table[522] = GetProcAddress(sdl2Handle, "SDL_memmove");
	sdl2Table[523] = GetProcAddress(sdl2Handle, "SDL_memset");
	sdl2Table[524] = GetProcAddress(sdl2Handle, "SDL_pow");
	sdl2Table[525] = GetProcAddress(sdl2Handle, "SDL_qsort");
	sdl2Table[526] = GetProcAddress(sdl2Handle, "SDL_realloc");
	sdl2Table[527] = GetProcAddress(sdl2Handle, "SDL_scalbn");
	sdl2Table[528] = GetProcAddress(sdl2Handle, "SDL_setenv");
	sdl2Table[529] = GetProcAddress(sdl2Handle, "SDL_sin");
	sdl2Table[530] = GetProcAddress(sdl2Handle, "SDL_sinf");
	sdl2Table[531] = GetProcAddress(sdl2Handle, "SDL_snprintf");
	sdl2Table[532] = GetProcAddress(sdl2Handle, "SDL_sqrt");
	sdl2Table[533] = GetProcAddress(sdl2Handle, "SDL_sqrtf");
	sdl2Table[534] = GetProcAddress(sdl2Handle, "SDL_sscanf");
	sdl2Table[535] = GetProcAddress(sdl2Handle, "SDL_strcasecmp");
	sdl2Table[536] = GetProcAddress(sdl2Handle, "SDL_strchr");
	sdl2Table[537] = GetProcAddress(sdl2Handle, "SDL_strcmp");
	sdl2Table[538] = GetProcAddress(sdl2Handle, "SDL_strdup");
	sdl2Table[539] = GetProcAddress(sdl2Handle, "SDL_strlcat");
	sdl2Table[540] = GetProcAddress(sdl2Handle, "SDL_strlcpy");
	sdl2Table[541] = GetProcAddress(sdl2Handle, "SDL_strlen");
	sdl2Table[542] = GetProcAddress(sdl2Handle, "SDL_strlwr");
	sdl2Table[543] = GetProcAddress(sdl2Handle, "SDL_strncasecmp");
	sdl2Table[544] = GetProcAddress(sdl2Handle, "SDL_strncmp");
	sdl2Table[545] = GetProcAddress(sdl2Handle, "SDL_strrchr");
	sdl2Table[546] = GetProcAddress(sdl2Handle, "SDL_strrev");
	sdl2Table[547] = GetProcAddress(sdl2Handle, "SDL_strstr");
	sdl2Table[548] = GetProcAddress(sdl2Handle, "SDL_strtod");
	sdl2Table[549] = GetProcAddress(sdl2Handle, "SDL_strtol");
	sdl2Table[550] = GetProcAddress(sdl2Handle, "SDL_strtoll");
	sdl2Table[551] = GetProcAddress(sdl2Handle, "SDL_strtoul");
	sdl2Table[552] = GetProcAddress(sdl2Handle, "SDL_strtoull");
	sdl2Table[553] = GetProcAddress(sdl2Handle, "SDL_strupr");
	sdl2Table[554] = GetProcAddress(sdl2Handle, "SDL_tan");
	sdl2Table[555] = GetProcAddress(sdl2Handle, "SDL_tanf");
	sdl2Table[556] = GetProcAddress(sdl2Handle, "SDL_tolower");
	sdl2Table[557] = GetProcAddress(sdl2Handle, "SDL_toupper");
	sdl2Table[558] = GetProcAddress(sdl2Handle, "SDL_uitoa");
	sdl2Table[559] = GetProcAddress(sdl2Handle, "SDL_ulltoa");
	sdl2Table[560] = GetProcAddress(sdl2Handle, "SDL_ultoa");
	sdl2Table[561] = GetProcAddress(sdl2Handle, "SDL_utf8strlcpy");
	sdl2Table[562] = GetProcAddress(sdl2Handle, "SDL_vsnprintf");
	sdl2Table[563] = GetProcAddress(sdl2Handle, "SDL_vsscanf");
	sdl2Table[564] = GetProcAddress(sdl2Handle, "SDL_wcslcat");
	sdl2Table[565] = GetProcAddress(sdl2Handle, "SDL_wcslcpy");
	sdl2Table[566] = GetProcAddress(sdl2Handle, "SDL_wcslen");

	return true;
}

#define PROXY(n) extern "C" __declspec(naked) void __stdcall __S__##n##__() { { __asm jmp sdl2Table[n * 4] } }
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
PROXY(123)
PROXY(124)
PROXY(125)
PROXY(126)
PROXY(127)
PROXY(128)
PROXY(129)
PROXY(130)
PROXY(131)
PROXY(132)
PROXY(133)
PROXY(134)
PROXY(135)
PROXY(136)
PROXY(137)
PROXY(138)
PROXY(139)
PROXY(140)
PROXY(141)
PROXY(142)
PROXY(143)
PROXY(144)
PROXY(145)
PROXY(146)
PROXY(147)
PROXY(148)
PROXY(149)
PROXY(150)
PROXY(151)
PROXY(152)
PROXY(153)
PROXY(154)
PROXY(155)
PROXY(156)
PROXY(157)
PROXY(158)
PROXY(159)
PROXY(160)
PROXY(161)
PROXY(162)
PROXY(163)
PROXY(164)
PROXY(165)
PROXY(166)
PROXY(167)
PROXY(168)
PROXY(169)
PROXY(170)
PROXY(171)
PROXY(172)
PROXY(173)
PROXY(174)
PROXY(175)
PROXY(176)
PROXY(177)
PROXY(178)
PROXY(179)
PROXY(180)
PROXY(181)
PROXY(182)
PROXY(183)
PROXY(184)
PROXY(185)
PROXY(186)
PROXY(187)
PROXY(188)
PROXY(189)
PROXY(190)
PROXY(191)
PROXY(192)
PROXY(193)
PROXY(194)
PROXY(195)
PROXY(196)
PROXY(197)
PROXY(198)
PROXY(199)
PROXY(200)
PROXY(201)
PROXY(202)
PROXY(203)
PROXY(204)
PROXY(205)
PROXY(206)
PROXY(207)
PROXY(208)
PROXY(209)
PROXY(210)
PROXY(211)
PROXY(212)
PROXY(213)
PROXY(214)
PROXY(215)
PROXY(216)
PROXY(217)
PROXY(218)
PROXY(219)
PROXY(220)
PROXY(221)
PROXY(222)
PROXY(223)
PROXY(224)
PROXY(225)
PROXY(226)
PROXY(227)
PROXY(228)
PROXY(229)
PROXY(230)
PROXY(231)
PROXY(232)
PROXY(233)
PROXY(234)
PROXY(235)
PROXY(236)
PROXY(237)
PROXY(238)
PROXY(239)
PROXY(240)
PROXY(241)
PROXY(242)
PROXY(243)
PROXY(244)
PROXY(245)
PROXY(246)
PROXY(247)
PROXY(248)
PROXY(249)
PROXY(250)
PROXY(251)
PROXY(252)
PROXY(253)
PROXY(254)
PROXY(255)
PROXY(256)
PROXY(257)
PROXY(258)
PROXY(259)
PROXY(260)
PROXY(261)
PROXY(262)
PROXY(263)
PROXY(264)
PROXY(265)
PROXY(266)
PROXY(267)
PROXY(268)
PROXY(269)
PROXY(270)
PROXY(271)
PROXY(272)
PROXY(273)
PROXY(274)
PROXY(275)
PROXY(276)
PROXY(277)
PROXY(278)
PROXY(279)
PROXY(280)
PROXY(281)
PROXY(282)
PROXY(283)
PROXY(284)
PROXY(285)
PROXY(286)
PROXY(287)
PROXY(288)
PROXY(289)
PROXY(290)
PROXY(291)
PROXY(292)
PROXY(293)
PROXY(294)
PROXY(295)
PROXY(296)
PROXY(297)
PROXY(298)
PROXY(299)
PROXY(300)
PROXY(301)
PROXY(302)
PROXY(303)
PROXY(304)
PROXY(305)
PROXY(306)
PROXY(307)
PROXY(308)
PROXY(309)
PROXY(310)
PROXY(311)
PROXY(312)
PROXY(313)
PROXY(314)
PROXY(315)
PROXY(316)
PROXY(317)
PROXY(318)
PROXY(319)
PROXY(320)
PROXY(321)
PROXY(322)
PROXY(323)
PROXY(324)
PROXY(325)
PROXY(326)
PROXY(327)
PROXY(328)
PROXY(329)
PROXY(330)
PROXY(331)
PROXY(332)
PROXY(333)
PROXY(334)
PROXY(335)
PROXY(336)
PROXY(337)
PROXY(338)
PROXY(339)
PROXY(340)
PROXY(341)
PROXY(342)
PROXY(343)
PROXY(344)
PROXY(345)
PROXY(346)
PROXY(347)
PROXY(348)
PROXY(349)
PROXY(350)
PROXY(351)
PROXY(352)
PROXY(353)
PROXY(354)
PROXY(355)
PROXY(356)
PROXY(357)
PROXY(358)
PROXY(359)
PROXY(360)
PROXY(361)
PROXY(362)
PROXY(363)
PROXY(364)
PROXY(365)
PROXY(366)
PROXY(367)
PROXY(368)
PROXY(369)
PROXY(370)
PROXY(371)
PROXY(372)
PROXY(373)
PROXY(374)
PROXY(375)
PROXY(376)
PROXY(377)
PROXY(378)
PROXY(379)
PROXY(380)
PROXY(381)
PROXY(382)
PROXY(383)
PROXY(384)
PROXY(385)
PROXY(386)
PROXY(387)
PROXY(388)
PROXY(389)
PROXY(390)
PROXY(391)
PROXY(392)
PROXY(393)
PROXY(394)
PROXY(395)
PROXY(396)
PROXY(397)
PROXY(398)
PROXY(399)
PROXY(400)
PROXY(401)
PROXY(402)
PROXY(403)
PROXY(404)
PROXY(405)
PROXY(406)
PROXY(407)
PROXY(408)
PROXY(409)
PROXY(410)
PROXY(411)
PROXY(412)
PROXY(413)
PROXY(414)
PROXY(415)
PROXY(416)
PROXY(417)
PROXY(418)
PROXY(419)
PROXY(420)
PROXY(421)
PROXY(422)
PROXY(423)
PROXY(424)
PROXY(425)
PROXY(426)
PROXY(427)
PROXY(428)
PROXY(429)
PROXY(430)
PROXY(431)
PROXY(432)
PROXY(433)
PROXY(434)
PROXY(435)
PROXY(436)
PROXY(437)
PROXY(438)
PROXY(439)
PROXY(440)
PROXY(441)
PROXY(442)
PROXY(443)
PROXY(444)
PROXY(445)
PROXY(446)
PROXY(447)
PROXY(448)
PROXY(449)
PROXY(450)
PROXY(451)
PROXY(452)
PROXY(453)
PROXY(454)
PROXY(455)
PROXY(456)
PROXY(457)
PROXY(458)
PROXY(459)
PROXY(460)
PROXY(461)
PROXY(462)
PROXY(463)
PROXY(464)
PROXY(465)
PROXY(466)
PROXY(467)
PROXY(468)
PROXY(469)
PROXY(470)
PROXY(471)
PROXY(472)
PROXY(473)
PROXY(474)
PROXY(475)
PROXY(476)
PROXY(477)
PROXY(478)
PROXY(479)
PROXY(480)
PROXY(481)
PROXY(482)
PROXY(483)
PROXY(484)
PROXY(485)
PROXY(486)
PROXY(487)
PROXY(488)
PROXY(489)
PROXY(490)
PROXY(491)
PROXY(492)
PROXY(493)
PROXY(494)
PROXY(495)
PROXY(496)
PROXY(497)
PROXY(498)
PROXY(499)
PROXY(500)
PROXY(501)
PROXY(502)
PROXY(503)
PROXY(504)
PROXY(505)
PROXY(506)
PROXY(507)
PROXY(508)
PROXY(509)
PROXY(510)
PROXY(511)
PROXY(512)
PROXY(513)
PROXY(514)
PROXY(515)
PROXY(516)
PROXY(517)
PROXY(518)
PROXY(519)
PROXY(520)
PROXY(521)
PROXY(522)
PROXY(523)
PROXY(524)
PROXY(525)
PROXY(526)
PROXY(527)
PROXY(528)
PROXY(529)
PROXY(530)
PROXY(531)
PROXY(532)
PROXY(533)
PROXY(534)
PROXY(535)
PROXY(536)
PROXY(537)
PROXY(538)
PROXY(539)
PROXY(540)
PROXY(541)
PROXY(542)
PROXY(543)
PROXY(544)
PROXY(545)
PROXY(546)
PROXY(547)
PROXY(548)
PROXY(549)
PROXY(550)
PROXY(551)
PROXY(552)
PROXY(553)
PROXY(554)
PROXY(555)
PROXY(556)
PROXY(557)
PROXY(558)
PROXY(559)
PROXY(560)
PROXY(561)
PROXY(562)
PROXY(563)
PROXY(564)
PROXY(565)
PROXY(566)
#undef PROXY
