#include <windows.h>
#pragma pack(1)

static HINSTANCE opengl32Handle = 0;
FARPROC opengl32Table[368] = { 0 };

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID) {
	if(reason == DLL_PROCESS_DETACH && opengl32Handle!=NULL) {
		FreeLibrary(opengl32Handle);
		return 0;
	}

	if(reason != DLL_PROCESS_ATTACH) {
		return 1;
	}

	opengl32Handle = LoadLibraryA("SDL2.dll");
	if(opengl32Handle==NULL) return 1;
	
	opengl32Table[0] = GetProcAddress(opengl32Handle, "GlmfBeginGlsBlock");
	opengl32Table[1] = GetProcAddress(opengl32Handle, "GlmfCloseMetaFile");
	opengl32Table[2] = GetProcAddress(opengl32Handle, "GlmfEndGlsBlock");
	opengl32Table[3] = GetProcAddress(opengl32Handle, "GlmfEndPlayback");
	opengl32Table[4] = GetProcAddress(opengl32Handle, "GlmfInitPlayback");
	opengl32Table[5] = GetProcAddress(opengl32Handle, "GlmfPlayGlsRecord");
	opengl32Table[6] = GetProcAddress(opengl32Handle, "glAccum");
	opengl32Table[7] = GetProcAddress(opengl32Handle, "glAlphaFunc");
	opengl32Table[8] = GetProcAddress(opengl32Handle, "glAreTexturesResident");
	opengl32Table[9] = GetProcAddress(opengl32Handle, "glArrayElement");
	opengl32Table[10] = GetProcAddress(opengl32Handle, "glBegin");
	opengl32Table[11] = GetProcAddress(opengl32Handle, "glBindTexture");
	opengl32Table[12] = GetProcAddress(opengl32Handle, "glBitmap");
	opengl32Table[13] = GetProcAddress(opengl32Handle, "glBlendFunc");
	opengl32Table[14] = GetProcAddress(opengl32Handle, "glCallList");
	opengl32Table[15] = GetProcAddress(opengl32Handle, "glCallLists");
	opengl32Table[16] = GetProcAddress(opengl32Handle, "glClear");
	opengl32Table[17] = GetProcAddress(opengl32Handle, "glClearAccum");
	opengl32Table[18] = GetProcAddress(opengl32Handle, "glClearColor");
	opengl32Table[19] = GetProcAddress(opengl32Handle, "glClearDepth");
	opengl32Table[20] = GetProcAddress(opengl32Handle, "glClearIndex");
	opengl32Table[21] = GetProcAddress(opengl32Handle, "glClearStencil");
	opengl32Table[22] = GetProcAddress(opengl32Handle, "glClipPlane");
	opengl32Table[23] = GetProcAddress(opengl32Handle, "glColor3b");
	opengl32Table[24] = GetProcAddress(opengl32Handle, "glColor3bv");
	opengl32Table[25] = GetProcAddress(opengl32Handle, "glColor3d");
	opengl32Table[26] = GetProcAddress(opengl32Handle, "glColor3dv");
	opengl32Table[27] = GetProcAddress(opengl32Handle, "glColor3f");
	opengl32Table[28] = GetProcAddress(opengl32Handle, "glColor3fv");
	opengl32Table[29] = GetProcAddress(opengl32Handle, "glColor3i");
	opengl32Table[30] = GetProcAddress(opengl32Handle, "glColor3iv");
	opengl32Table[31] = GetProcAddress(opengl32Handle, "glColor3s");
	opengl32Table[32] = GetProcAddress(opengl32Handle, "glColor3sv");
	opengl32Table[33] = GetProcAddress(opengl32Handle, "glColor3ub");
	opengl32Table[34] = GetProcAddress(opengl32Handle, "glColor3ubv");
	opengl32Table[35] = GetProcAddress(opengl32Handle, "glColor3ui");
	opengl32Table[36] = GetProcAddress(opengl32Handle, "glColor3uiv");
	opengl32Table[37] = GetProcAddress(opengl32Handle, "glColor3us");
	opengl32Table[38] = GetProcAddress(opengl32Handle, "glColor3usv");
	opengl32Table[39] = GetProcAddress(opengl32Handle, "glColor4b");
	opengl32Table[40] = GetProcAddress(opengl32Handle, "glColor4bv");
	opengl32Table[41] = GetProcAddress(opengl32Handle, "glColor4d");
	opengl32Table[42] = GetProcAddress(opengl32Handle, "glColor4dv");
	opengl32Table[43] = GetProcAddress(opengl32Handle, "glColor4f");
	opengl32Table[44] = GetProcAddress(opengl32Handle, "glColor4fv");
	opengl32Table[45] = GetProcAddress(opengl32Handle, "glColor4i");
	opengl32Table[46] = GetProcAddress(opengl32Handle, "glColor4iv");
	opengl32Table[47] = GetProcAddress(opengl32Handle, "glColor4s");
	opengl32Table[48] = GetProcAddress(opengl32Handle, "glColor4sv");
	opengl32Table[49] = GetProcAddress(opengl32Handle, "glColor4ub");
	opengl32Table[50] = GetProcAddress(opengl32Handle, "glColor4ubv");
	opengl32Table[51] = GetProcAddress(opengl32Handle, "glColor4ui");
	opengl32Table[52] = GetProcAddress(opengl32Handle, "glColor4uiv");
	opengl32Table[53] = GetProcAddress(opengl32Handle, "glColor4us");
	opengl32Table[54] = GetProcAddress(opengl32Handle, "glColor4usv");
	opengl32Table[55] = GetProcAddress(opengl32Handle, "glColorMask");
	opengl32Table[56] = GetProcAddress(opengl32Handle, "glColorMaterial");
	opengl32Table[57] = GetProcAddress(opengl32Handle, "glColorPointer");
	opengl32Table[58] = GetProcAddress(opengl32Handle, "glCopyPixels");
	opengl32Table[59] = GetProcAddress(opengl32Handle, "glCopyTexImage1D");
	opengl32Table[60] = GetProcAddress(opengl32Handle, "glCopyTexImage2D");
	opengl32Table[61] = GetProcAddress(opengl32Handle, "glCopyTexSubImage1D");
	opengl32Table[62] = GetProcAddress(opengl32Handle, "glCopyTexSubImage2D");
	opengl32Table[63] = GetProcAddress(opengl32Handle, "glCullFace");
	opengl32Table[64] = GetProcAddress(opengl32Handle, "glDebugEntry");
	opengl32Table[65] = GetProcAddress(opengl32Handle, "glDeleteLists");
	opengl32Table[66] = GetProcAddress(opengl32Handle, "glDeleteTextures");
	opengl32Table[67] = GetProcAddress(opengl32Handle, "glDepthFunc");
	opengl32Table[68] = GetProcAddress(opengl32Handle, "glDepthMask");
	opengl32Table[69] = GetProcAddress(opengl32Handle, "glDepthRange");
	opengl32Table[70] = GetProcAddress(opengl32Handle, "glDisable");
	opengl32Table[71] = GetProcAddress(opengl32Handle, "glDisableClientState");
	opengl32Table[72] = GetProcAddress(opengl32Handle, "glDrawArrays");
	opengl32Table[73] = GetProcAddress(opengl32Handle, "glDrawBuffer");
	opengl32Table[74] = GetProcAddress(opengl32Handle, "glDrawElements");
	opengl32Table[75] = GetProcAddress(opengl32Handle, "glDrawPixels");
	opengl32Table[76] = GetProcAddress(opengl32Handle, "glEdgeFlag");
	opengl32Table[77] = GetProcAddress(opengl32Handle, "glEdgeFlagPointer");
	opengl32Table[78] = GetProcAddress(opengl32Handle, "glEdgeFlagv");
	opengl32Table[79] = GetProcAddress(opengl32Handle, "glEnable");
	opengl32Table[80] = GetProcAddress(opengl32Handle, "glEnableClientState");
	opengl32Table[81] = GetProcAddress(opengl32Handle, "glEnd");
	opengl32Table[82] = GetProcAddress(opengl32Handle, "glEndList");
	opengl32Table[83] = GetProcAddress(opengl32Handle, "glEvalCoord1d");
	opengl32Table[84] = GetProcAddress(opengl32Handle, "glEvalCoord1dv");
	opengl32Table[85] = GetProcAddress(opengl32Handle, "glEvalCoord1f");
	opengl32Table[86] = GetProcAddress(opengl32Handle, "glEvalCoord1fv");
	opengl32Table[87] = GetProcAddress(opengl32Handle, "glEvalCoord2d");
	opengl32Table[88] = GetProcAddress(opengl32Handle, "glEvalCoord2dv");
	opengl32Table[89] = GetProcAddress(opengl32Handle, "glEvalCoord2f");
	opengl32Table[90] = GetProcAddress(opengl32Handle, "glEvalCoord2fv");
	opengl32Table[91] = GetProcAddress(opengl32Handle, "glEvalMesh1");
	opengl32Table[92] = GetProcAddress(opengl32Handle, "glEvalMesh2");
	opengl32Table[93] = GetProcAddress(opengl32Handle, "glEvalPoint1");
	opengl32Table[94] = GetProcAddress(opengl32Handle, "glEvalPoint2");
	opengl32Table[95] = GetProcAddress(opengl32Handle, "glFeedbackBuffer");
	opengl32Table[96] = GetProcAddress(opengl32Handle, "glFinish");
	opengl32Table[97] = GetProcAddress(opengl32Handle, "glFlush");
	opengl32Table[98] = GetProcAddress(opengl32Handle, "glFogf");
	opengl32Table[99] = GetProcAddress(opengl32Handle, "glFogfv");
	opengl32Table[100] = GetProcAddress(opengl32Handle, "glFogi");
	opengl32Table[101] = GetProcAddress(opengl32Handle, "glFogiv");
	opengl32Table[102] = GetProcAddress(opengl32Handle, "glFrontFace");
	opengl32Table[103] = GetProcAddress(opengl32Handle, "glFrustum");
	opengl32Table[104] = GetProcAddress(opengl32Handle, "glGenLists");
	opengl32Table[105] = GetProcAddress(opengl32Handle, "glGenTextures");
	opengl32Table[106] = GetProcAddress(opengl32Handle, "glGetBooleanv");
	opengl32Table[107] = GetProcAddress(opengl32Handle, "glGetClipPlane");
	opengl32Table[108] = GetProcAddress(opengl32Handle, "glGetDoublev");
	opengl32Table[109] = GetProcAddress(opengl32Handle, "glGetError");
	opengl32Table[110] = GetProcAddress(opengl32Handle, "glGetFloatv");
	opengl32Table[111] = GetProcAddress(opengl32Handle, "glGetIntegerv");
	opengl32Table[112] = GetProcAddress(opengl32Handle, "glGetLightfv");
	opengl32Table[113] = GetProcAddress(opengl32Handle, "glGetLightiv");
	opengl32Table[114] = GetProcAddress(opengl32Handle, "glGetMapdv");
	opengl32Table[115] = GetProcAddress(opengl32Handle, "glGetMapfv");
	opengl32Table[116] = GetProcAddress(opengl32Handle, "glGetMapiv");
	opengl32Table[117] = GetProcAddress(opengl32Handle, "glGetMaterialfv");
	opengl32Table[118] = GetProcAddress(opengl32Handle, "glGetMaterialiv");
	opengl32Table[119] = GetProcAddress(opengl32Handle, "glGetPixelMapfv");
	opengl32Table[120] = GetProcAddress(opengl32Handle, "glGetPixelMapuiv");
	opengl32Table[121] = GetProcAddress(opengl32Handle, "glGetPixelMapusv");
	opengl32Table[122] = GetProcAddress(opengl32Handle, "glGetPointerv");
	opengl32Table[123] = GetProcAddress(opengl32Handle, "glGetPolygonStipple");
	opengl32Table[124] = GetProcAddress(opengl32Handle, "glGetString");
	opengl32Table[125] = GetProcAddress(opengl32Handle, "glGetTexEnvfv");
	opengl32Table[126] = GetProcAddress(opengl32Handle, "glGetTexEnviv");
	opengl32Table[127] = GetProcAddress(opengl32Handle, "glGetTexGendv");
	opengl32Table[128] = GetProcAddress(opengl32Handle, "glGetTexGenfv");
	opengl32Table[129] = GetProcAddress(opengl32Handle, "glGetTexGeniv");
	opengl32Table[130] = GetProcAddress(opengl32Handle, "glGetTexImage");
	opengl32Table[131] = GetProcAddress(opengl32Handle, "glGetTexLevelParameterfv");
	opengl32Table[132] = GetProcAddress(opengl32Handle, "glGetTexLevelParameteriv");
	opengl32Table[133] = GetProcAddress(opengl32Handle, "glGetTexParameterfv");
	opengl32Table[134] = GetProcAddress(opengl32Handle, "glGetTexParameteriv");
	opengl32Table[135] = GetProcAddress(opengl32Handle, "glHint");
	opengl32Table[136] = GetProcAddress(opengl32Handle, "glIndexMask");
	opengl32Table[137] = GetProcAddress(opengl32Handle, "glIndexPointer");
	opengl32Table[138] = GetProcAddress(opengl32Handle, "glIndexd");
	opengl32Table[139] = GetProcAddress(opengl32Handle, "glIndexdv");
	opengl32Table[140] = GetProcAddress(opengl32Handle, "glIndexf");
	opengl32Table[141] = GetProcAddress(opengl32Handle, "glIndexfv");
	opengl32Table[142] = GetProcAddress(opengl32Handle, "glIndexi");
	opengl32Table[143] = GetProcAddress(opengl32Handle, "glIndexiv");
	opengl32Table[144] = GetProcAddress(opengl32Handle, "glIndexs");
	opengl32Table[145] = GetProcAddress(opengl32Handle, "glIndexsv");
	opengl32Table[146] = GetProcAddress(opengl32Handle, "glIndexub");
	opengl32Table[147] = GetProcAddress(opengl32Handle, "glIndexubv");
	opengl32Table[148] = GetProcAddress(opengl32Handle, "glInitNames");
	opengl32Table[149] = GetProcAddress(opengl32Handle, "glInterleavedArrays");
	opengl32Table[150] = GetProcAddress(opengl32Handle, "glIsEnabled");
	opengl32Table[151] = GetProcAddress(opengl32Handle, "glIsList");
	opengl32Table[152] = GetProcAddress(opengl32Handle, "glIsTexture");
	opengl32Table[153] = GetProcAddress(opengl32Handle, "glLightModelf");
	opengl32Table[154] = GetProcAddress(opengl32Handle, "glLightModelfv");
	opengl32Table[155] = GetProcAddress(opengl32Handle, "glLightModeli");
	opengl32Table[156] = GetProcAddress(opengl32Handle, "glLightModeliv");
	opengl32Table[157] = GetProcAddress(opengl32Handle, "glLightf");
	opengl32Table[158] = GetProcAddress(opengl32Handle, "glLightfv");
	opengl32Table[159] = GetProcAddress(opengl32Handle, "glLighti");
	opengl32Table[160] = GetProcAddress(opengl32Handle, "glLightiv");
	opengl32Table[161] = GetProcAddress(opengl32Handle, "glLineStipple");
	opengl32Table[162] = GetProcAddress(opengl32Handle, "glLineWidth");
	opengl32Table[163] = GetProcAddress(opengl32Handle, "glListBase");
	opengl32Table[164] = GetProcAddress(opengl32Handle, "glLoadIdentity");
	opengl32Table[165] = GetProcAddress(opengl32Handle, "glLoadMatrixd");
	opengl32Table[166] = GetProcAddress(opengl32Handle, "glLoadMatrixf");
	opengl32Table[167] = GetProcAddress(opengl32Handle, "glLoadName");
	opengl32Table[168] = GetProcAddress(opengl32Handle, "glLogicOp");
	opengl32Table[169] = GetProcAddress(opengl32Handle, "glMap1d");
	opengl32Table[170] = GetProcAddress(opengl32Handle, "glMap1f");
	opengl32Table[171] = GetProcAddress(opengl32Handle, "glMap2d");
	opengl32Table[172] = GetProcAddress(opengl32Handle, "glMap2f");
	opengl32Table[173] = GetProcAddress(opengl32Handle, "glMapGrid1d");
	opengl32Table[174] = GetProcAddress(opengl32Handle, "glMapGrid1f");
	opengl32Table[175] = GetProcAddress(opengl32Handle, "glMapGrid2d");
	opengl32Table[176] = GetProcAddress(opengl32Handle, "glMapGrid2f");
	opengl32Table[177] = GetProcAddress(opengl32Handle, "glMaterialf");
	opengl32Table[178] = GetProcAddress(opengl32Handle, "glMaterialfv");
	opengl32Table[179] = GetProcAddress(opengl32Handle, "glMateriali");
	opengl32Table[180] = GetProcAddress(opengl32Handle, "glMaterialiv");
	opengl32Table[181] = GetProcAddress(opengl32Handle, "glMatrixMode");
	opengl32Table[182] = GetProcAddress(opengl32Handle, "glMultMatrixd");
	opengl32Table[183] = GetProcAddress(opengl32Handle, "glMultMatrixf");
	opengl32Table[184] = GetProcAddress(opengl32Handle, "glNewList");
	opengl32Table[185] = GetProcAddress(opengl32Handle, "glNormal3b");
	opengl32Table[186] = GetProcAddress(opengl32Handle, "glNormal3bv");
	opengl32Table[187] = GetProcAddress(opengl32Handle, "glNormal3d");
	opengl32Table[188] = GetProcAddress(opengl32Handle, "glNormal3dv");
	opengl32Table[189] = GetProcAddress(opengl32Handle, "glNormal3f");
	opengl32Table[190] = GetProcAddress(opengl32Handle, "glNormal3fv");
	opengl32Table[191] = GetProcAddress(opengl32Handle, "glNormal3i");
	opengl32Table[192] = GetProcAddress(opengl32Handle, "glNormal3iv");
	opengl32Table[193] = GetProcAddress(opengl32Handle, "glNormal3s");
	opengl32Table[194] = GetProcAddress(opengl32Handle, "glNormal3sv");
	opengl32Table[195] = GetProcAddress(opengl32Handle, "glNormalPointer");
	opengl32Table[196] = GetProcAddress(opengl32Handle, "glOrtho");
	opengl32Table[197] = GetProcAddress(opengl32Handle, "glPassThrough");
	opengl32Table[198] = GetProcAddress(opengl32Handle, "glPixelMapfv");
	opengl32Table[199] = GetProcAddress(opengl32Handle, "glPixelMapuiv");
	opengl32Table[200] = GetProcAddress(opengl32Handle, "glPixelMapusv");
	opengl32Table[201] = GetProcAddress(opengl32Handle, "glPixelStoref");
	opengl32Table[202] = GetProcAddress(opengl32Handle, "glPixelStorei");
	opengl32Table[203] = GetProcAddress(opengl32Handle, "glPixelTransferf");
	opengl32Table[204] = GetProcAddress(opengl32Handle, "glPixelTransferi");
	opengl32Table[205] = GetProcAddress(opengl32Handle, "glPixelZoom");
	opengl32Table[206] = GetProcAddress(opengl32Handle, "glPointSize");
	opengl32Table[207] = GetProcAddress(opengl32Handle, "glPolygonMode");
	opengl32Table[208] = GetProcAddress(opengl32Handle, "glPolygonOffset");
	opengl32Table[209] = GetProcAddress(opengl32Handle, "glPolygonStipple");
	opengl32Table[210] = GetProcAddress(opengl32Handle, "glPopAttrib");
	opengl32Table[211] = GetProcAddress(opengl32Handle, "glPopClientAttrib");
	opengl32Table[212] = GetProcAddress(opengl32Handle, "glPopMatrix");
	opengl32Table[213] = GetProcAddress(opengl32Handle, "glPopName");
	opengl32Table[214] = GetProcAddress(opengl32Handle, "glPrioritizeTextures");
	opengl32Table[215] = GetProcAddress(opengl32Handle, "glPushAttrib");
	opengl32Table[216] = GetProcAddress(opengl32Handle, "glPushClientAttrib");
	opengl32Table[217] = GetProcAddress(opengl32Handle, "glPushMatrix");
	opengl32Table[218] = GetProcAddress(opengl32Handle, "glPushName");
	opengl32Table[219] = GetProcAddress(opengl32Handle, "glRasterPos2d");
	opengl32Table[220] = GetProcAddress(opengl32Handle, "glRasterPos2dv");
	opengl32Table[221] = GetProcAddress(opengl32Handle, "glRasterPos2f");
	opengl32Table[222] = GetProcAddress(opengl32Handle, "glRasterPos2fv");
	opengl32Table[223] = GetProcAddress(opengl32Handle, "glRasterPos2i");
	opengl32Table[224] = GetProcAddress(opengl32Handle, "glRasterPos2iv");
	opengl32Table[225] = GetProcAddress(opengl32Handle, "glRasterPos2s");
	opengl32Table[226] = GetProcAddress(opengl32Handle, "glRasterPos2sv");
	opengl32Table[227] = GetProcAddress(opengl32Handle, "glRasterPos3d");
	opengl32Table[228] = GetProcAddress(opengl32Handle, "glRasterPos3dv");
	opengl32Table[229] = GetProcAddress(opengl32Handle, "glRasterPos3f");
	opengl32Table[230] = GetProcAddress(opengl32Handle, "glRasterPos3fv");
	opengl32Table[231] = GetProcAddress(opengl32Handle, "glRasterPos3i");
	opengl32Table[232] = GetProcAddress(opengl32Handle, "glRasterPos3iv");
	opengl32Table[233] = GetProcAddress(opengl32Handle, "glRasterPos3s");
	opengl32Table[234] = GetProcAddress(opengl32Handle, "glRasterPos3sv");
	opengl32Table[235] = GetProcAddress(opengl32Handle, "glRasterPos4d");
	opengl32Table[236] = GetProcAddress(opengl32Handle, "glRasterPos4dv");
	opengl32Table[237] = GetProcAddress(opengl32Handle, "glRasterPos4f");
	opengl32Table[238] = GetProcAddress(opengl32Handle, "glRasterPos4fv");
	opengl32Table[239] = GetProcAddress(opengl32Handle, "glRasterPos4i");
	opengl32Table[240] = GetProcAddress(opengl32Handle, "glRasterPos4iv");
	opengl32Table[241] = GetProcAddress(opengl32Handle, "glRasterPos4s");
	opengl32Table[242] = GetProcAddress(opengl32Handle, "glRasterPos4sv");
	opengl32Table[243] = GetProcAddress(opengl32Handle, "glReadBuffer");
	opengl32Table[244] = GetProcAddress(opengl32Handle, "glReadPixels");
	opengl32Table[245] = GetProcAddress(opengl32Handle, "glRectd");
	opengl32Table[246] = GetProcAddress(opengl32Handle, "glRectdv");
	opengl32Table[247] = GetProcAddress(opengl32Handle, "glRectf");
	opengl32Table[248] = GetProcAddress(opengl32Handle, "glRectfv");
	opengl32Table[249] = GetProcAddress(opengl32Handle, "glRecti");
	opengl32Table[250] = GetProcAddress(opengl32Handle, "glRectiv");
	opengl32Table[251] = GetProcAddress(opengl32Handle, "glRects");
	opengl32Table[252] = GetProcAddress(opengl32Handle, "glRectsv");
	opengl32Table[253] = GetProcAddress(opengl32Handle, "glRenderMode");
	opengl32Table[254] = GetProcAddress(opengl32Handle, "glRotated");
	opengl32Table[255] = GetProcAddress(opengl32Handle, "glRotatef");
	opengl32Table[256] = GetProcAddress(opengl32Handle, "glScaled");
	opengl32Table[257] = GetProcAddress(opengl32Handle, "glScalef");
	opengl32Table[258] = GetProcAddress(opengl32Handle, "glScissor");
	opengl32Table[259] = GetProcAddress(opengl32Handle, "glSelectBuffer");
	opengl32Table[260] = GetProcAddress(opengl32Handle, "glShadeModel");
	opengl32Table[261] = GetProcAddress(opengl32Handle, "glStencilFunc");
	opengl32Table[262] = GetProcAddress(opengl32Handle, "glStencilMask");
	opengl32Table[263] = GetProcAddress(opengl32Handle, "glStencilOp");
	opengl32Table[264] = GetProcAddress(opengl32Handle, "glTexCoord1d");
	opengl32Table[265] = GetProcAddress(opengl32Handle, "glTexCoord1dv");
	opengl32Table[266] = GetProcAddress(opengl32Handle, "glTexCoord1f");
	opengl32Table[267] = GetProcAddress(opengl32Handle, "glTexCoord1fv");
	opengl32Table[268] = GetProcAddress(opengl32Handle, "glTexCoord1i");
	opengl32Table[269] = GetProcAddress(opengl32Handle, "glTexCoord1iv");
	opengl32Table[270] = GetProcAddress(opengl32Handle, "glTexCoord1s");
	opengl32Table[271] = GetProcAddress(opengl32Handle, "glTexCoord1sv");
	opengl32Table[272] = GetProcAddress(opengl32Handle, "glTexCoord2d");
	opengl32Table[273] = GetProcAddress(opengl32Handle, "glTexCoord2dv");
	opengl32Table[274] = GetProcAddress(opengl32Handle, "glTexCoord2f");
	opengl32Table[275] = GetProcAddress(opengl32Handle, "glTexCoord2fv");
	opengl32Table[276] = GetProcAddress(opengl32Handle, "glTexCoord2i");
	opengl32Table[277] = GetProcAddress(opengl32Handle, "glTexCoord2iv");
	opengl32Table[278] = GetProcAddress(opengl32Handle, "glTexCoord2s");
	opengl32Table[279] = GetProcAddress(opengl32Handle, "glTexCoord2sv");
	opengl32Table[280] = GetProcAddress(opengl32Handle, "glTexCoord3d");
	opengl32Table[281] = GetProcAddress(opengl32Handle, "glTexCoord3dv");
	opengl32Table[282] = GetProcAddress(opengl32Handle, "glTexCoord3f");
	opengl32Table[283] = GetProcAddress(opengl32Handle, "glTexCoord3fv");
	opengl32Table[284] = GetProcAddress(opengl32Handle, "glTexCoord3i");
	opengl32Table[285] = GetProcAddress(opengl32Handle, "glTexCoord3iv");
	opengl32Table[286] = GetProcAddress(opengl32Handle, "glTexCoord3s");
	opengl32Table[287] = GetProcAddress(opengl32Handle, "glTexCoord3sv");
	opengl32Table[288] = GetProcAddress(opengl32Handle, "glTexCoord4d");
	opengl32Table[289] = GetProcAddress(opengl32Handle, "glTexCoord4dv");
	opengl32Table[290] = GetProcAddress(opengl32Handle, "glTexCoord4f");
	opengl32Table[291] = GetProcAddress(opengl32Handle, "glTexCoord4fv");
	opengl32Table[292] = GetProcAddress(opengl32Handle, "glTexCoord4i");
	opengl32Table[293] = GetProcAddress(opengl32Handle, "glTexCoord4iv");
	opengl32Table[294] = GetProcAddress(opengl32Handle, "glTexCoord4s");
	opengl32Table[295] = GetProcAddress(opengl32Handle, "glTexCoord4sv");
	opengl32Table[296] = GetProcAddress(opengl32Handle, "glTexCoordPointer");
	opengl32Table[297] = GetProcAddress(opengl32Handle, "glTexEnvf");
	opengl32Table[298] = GetProcAddress(opengl32Handle, "glTexEnvfv");
	opengl32Table[299] = GetProcAddress(opengl32Handle, "glTexEnvi");
	opengl32Table[300] = GetProcAddress(opengl32Handle, "glTexEnviv");
	opengl32Table[301] = GetProcAddress(opengl32Handle, "glTexGend");
	opengl32Table[302] = GetProcAddress(opengl32Handle, "glTexGendv");
	opengl32Table[303] = GetProcAddress(opengl32Handle, "glTexGenf");
	opengl32Table[304] = GetProcAddress(opengl32Handle, "glTexGenfv");
	opengl32Table[305] = GetProcAddress(opengl32Handle, "glTexGeni");
	opengl32Table[306] = GetProcAddress(opengl32Handle, "glTexGeniv");
	opengl32Table[307] = GetProcAddress(opengl32Handle, "glTexImage1D");
	opengl32Table[308] = GetProcAddress(opengl32Handle, "glTexImage2D");
	opengl32Table[309] = GetProcAddress(opengl32Handle, "glTexParameterf");
	opengl32Table[310] = GetProcAddress(opengl32Handle, "glTexParameterfv");
	opengl32Table[311] = GetProcAddress(opengl32Handle, "glTexParameteri");
	opengl32Table[312] = GetProcAddress(opengl32Handle, "glTexParameteriv");
	opengl32Table[313] = GetProcAddress(opengl32Handle, "glTexSubImage1D");
	opengl32Table[314] = GetProcAddress(opengl32Handle, "glTexSubImage2D");
	opengl32Table[315] = GetProcAddress(opengl32Handle, "glTranslated");
	opengl32Table[316] = GetProcAddress(opengl32Handle, "glTranslatef");
	opengl32Table[317] = GetProcAddress(opengl32Handle, "glVertex2d");
	opengl32Table[318] = GetProcAddress(opengl32Handle, "glVertex2dv");
	opengl32Table[319] = GetProcAddress(opengl32Handle, "glVertex2f");
	opengl32Table[320] = GetProcAddress(opengl32Handle, "glVertex2fv");
	opengl32Table[321] = GetProcAddress(opengl32Handle, "glVertex2i");
	opengl32Table[322] = GetProcAddress(opengl32Handle, "glVertex2iv");
	opengl32Table[323] = GetProcAddress(opengl32Handle, "glVertex2s");
	opengl32Table[324] = GetProcAddress(opengl32Handle, "glVertex2sv");
	opengl32Table[325] = GetProcAddress(opengl32Handle, "glVertex3d");
	opengl32Table[326] = GetProcAddress(opengl32Handle, "glVertex3dv");
	opengl32Table[327] = GetProcAddress(opengl32Handle, "glVertex3f");
	opengl32Table[328] = GetProcAddress(opengl32Handle, "glVertex3fv");
	opengl32Table[329] = GetProcAddress(opengl32Handle, "glVertex3i");
	opengl32Table[330] = GetProcAddress(opengl32Handle, "glVertex3iv");
	opengl32Table[331] = GetProcAddress(opengl32Handle, "glVertex3s");
	opengl32Table[332] = GetProcAddress(opengl32Handle, "glVertex3sv");
	opengl32Table[333] = GetProcAddress(opengl32Handle, "glVertex4d");
	opengl32Table[334] = GetProcAddress(opengl32Handle, "glVertex4dv");
	opengl32Table[335] = GetProcAddress(opengl32Handle, "glVertex4f");
	opengl32Table[336] = GetProcAddress(opengl32Handle, "glVertex4fv");
	opengl32Table[337] = GetProcAddress(opengl32Handle, "glVertex4i");
	opengl32Table[338] = GetProcAddress(opengl32Handle, "glVertex4iv");
	opengl32Table[339] = GetProcAddress(opengl32Handle, "glVertex4s");
	opengl32Table[340] = GetProcAddress(opengl32Handle, "glVertex4sv");
	opengl32Table[341] = GetProcAddress(opengl32Handle, "glVertexPointer");
	opengl32Table[342] = GetProcAddress(opengl32Handle, "glViewport");
	opengl32Table[343] = GetProcAddress(opengl32Handle, "wglChoosePixelFormat");
	opengl32Table[344] = GetProcAddress(opengl32Handle, "wglCopyContext");
	opengl32Table[345] = GetProcAddress(opengl32Handle, "wglCreateContext");
	opengl32Table[346] = GetProcAddress(opengl32Handle, "wglCreateLayerContext");
	opengl32Table[347] = GetProcAddress(opengl32Handle, "wglDeleteContext");
	opengl32Table[348] = GetProcAddress(opengl32Handle, "wglDescribeLayerPlane");
	opengl32Table[349] = GetProcAddress(opengl32Handle, "wglDescribePixelFormat");
	opengl32Table[350] = GetProcAddress(opengl32Handle, "wglGetCurrentContext");
	opengl32Table[351] = GetProcAddress(opengl32Handle, "wglGetCurrentDC");
	opengl32Table[352] = GetProcAddress(opengl32Handle, "wglGetDefaultProcAddress");
	opengl32Table[353] = GetProcAddress(opengl32Handle, "wglGetLayerPaletteEntries");
	opengl32Table[354] = GetProcAddress(opengl32Handle, "wglGetPixelFormat");
	opengl32Table[355] = GetProcAddress(opengl32Handle, "wglGetProcAddress");
	opengl32Table[356] = GetProcAddress(opengl32Handle, "wglMakeCurrent");
	opengl32Table[357] = GetProcAddress(opengl32Handle, "wglRealizeLayerPalette");
	opengl32Table[358] = GetProcAddress(opengl32Handle, "wglSetLayerPaletteEntries");
	opengl32Table[359] = GetProcAddress(opengl32Handle, "wglSetPixelFormat");
	opengl32Table[360] = GetProcAddress(opengl32Handle, "wglShareLists");
	opengl32Table[361] = GetProcAddress(opengl32Handle, "wglSwapBuffers");
	opengl32Table[362] = GetProcAddress(opengl32Handle, "wglSwapLayerBuffers");
	opengl32Table[363] = GetProcAddress(opengl32Handle, "wglSwapMultipleBuffers");
	opengl32Table[364] = GetProcAddress(opengl32Handle, "wglUseFontBitmapsA");
	opengl32Table[365] = GetProcAddress(opengl32Handle, "wglUseFontBitmapsW");
	opengl32Table[366] = GetProcAddress(opengl32Handle, "wglUseFontOutlinesA");
	opengl32Table[367] = GetProcAddress(opengl32Handle, "wglUseFontOutlinesW");

	return 1;
}

#define PROXY(n) extern "C" __declspec(naked) void __cdecl __G__##n##__() { { __asm jmp opengl32Table[n * 4] } }
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
#undef PROXY
