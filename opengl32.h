#ifndef __OPENGL_H__
#define __OPENGL_H__

#include <windows.h>

bool installOpenglHooks();

#define HOOK_OPENGL(name,rettype,args) \
rettype (__stdcall ** dll_##name) args = (rettype (__stdcall **) args) (void *) &opengl32Table[ OPENGL_N_##name ]; \
extern "C" __declspec(dllexport) rettype __stdcall hook_##name args

#define DECLARE_HOOK_OPENGL(name,rettype,args) \
extern rettype (__stdcall ** dll_##name) args; \
extern "C" rettype __stdcall hook_##name args;


extern FARPROC opengl32Table[];

#define OPENGL_N_GlmfBeginGlsBlock 0
#define OPENGL_N_GlmfCloseMetaFile 1
#define OPENGL_N_GlmfEndGlsBlock 2
#define OPENGL_N_GlmfEndPlayback 3
#define OPENGL_N_GlmfInitPlayback 4
#define OPENGL_N_GlmfPlayGlsRecord 5
#define OPENGL_N_glAccum 6
#define OPENGL_N_glAlphaFunc 7
#define OPENGL_N_glAreTexturesResident 8
#define OPENGL_N_glArrayElement 9
#define OPENGL_N_glBegin 10
#define OPENGL_N_glBindTexture 11
#define OPENGL_N_glBitmap 12
#define OPENGL_N_glBlendFunc 13
#define OPENGL_N_glCallList 14
#define OPENGL_N_glCallLists 15
#define OPENGL_N_glClear 16
#define OPENGL_N_glClearAccum 17
#define OPENGL_N_glClearColor 18
#define OPENGL_N_glClearDepth 19
#define OPENGL_N_glClearIndex 20
#define OPENGL_N_glClearStencil 21
#define OPENGL_N_glClipPlane 22
#define OPENGL_N_glColor3b 23
#define OPENGL_N_glColor3bv 24
#define OPENGL_N_glColor3d 25
#define OPENGL_N_glColor3dv 26
#define OPENGL_N_glColor3f 27
#define OPENGL_N_glColor3fv 28
#define OPENGL_N_glColor3i 29
#define OPENGL_N_glColor3iv 30
#define OPENGL_N_glColor3s 31
#define OPENGL_N_glColor3sv 32
#define OPENGL_N_glColor3ub 33
#define OPENGL_N_glColor3ubv 34
#define OPENGL_N_glColor3ui 35
#define OPENGL_N_glColor3uiv 36
#define OPENGL_N_glColor3us 37
#define OPENGL_N_glColor3usv 38
#define OPENGL_N_glColor4b 39
#define OPENGL_N_glColor4bv 40
#define OPENGL_N_glColor4d 41
#define OPENGL_N_glColor4dv 42
#define OPENGL_N_glColor4f 43
#define OPENGL_N_glColor4fv 44
#define OPENGL_N_glColor4i 45
#define OPENGL_N_glColor4iv 46
#define OPENGL_N_glColor4s 47
#define OPENGL_N_glColor4sv 48
#define OPENGL_N_glColor4ub 49
#define OPENGL_N_glColor4ubv 50
#define OPENGL_N_glColor4ui 51
#define OPENGL_N_glColor4uiv 52
#define OPENGL_N_glColor4us 53
#define OPENGL_N_glColor4usv 54
#define OPENGL_N_glColorMask 55
#define OPENGL_N_glColorMaterial 56
#define OPENGL_N_glColorPointer 57
#define OPENGL_N_glCopyPixels 58
#define OPENGL_N_glCopyTexImage1D 59
#define OPENGL_N_glCopyTexImage2D 60
#define OPENGL_N_glCopyTexSubImage1D 61
#define OPENGL_N_glCopyTexSubImage2D 62
#define OPENGL_N_glCullFace 63
#define OPENGL_N_glDebugEntry 64
#define OPENGL_N_glDeleteLists 65
#define OPENGL_N_glDeleteTextures 66
#define OPENGL_N_glDepthFunc 67
#define OPENGL_N_glDepthMask 68
#define OPENGL_N_glDepthRange 69
#define OPENGL_N_glDisable 70
#define OPENGL_N_glDisableClientState 71
#define OPENGL_N_glDrawArrays 72
#define OPENGL_N_glDrawBuffer 73
#define OPENGL_N_glDrawElements 74
#define OPENGL_N_glDrawPixels 75
#define OPENGL_N_glEdgeFlag 76
#define OPENGL_N_glEdgeFlagPointer 77
#define OPENGL_N_glEdgeFlagv 78
#define OPENGL_N_glEnable 79
#define OPENGL_N_glEnableClientState 80
#define OPENGL_N_glEnd 81
#define OPENGL_N_glEndList 82
#define OPENGL_N_glEvalCoord1d 83
#define OPENGL_N_glEvalCoord1dv 84
#define OPENGL_N_glEvalCoord1f 85
#define OPENGL_N_glEvalCoord1fv 86
#define OPENGL_N_glEvalCoord2d 87
#define OPENGL_N_glEvalCoord2dv 88
#define OPENGL_N_glEvalCoord2f 89
#define OPENGL_N_glEvalCoord2fv 90
#define OPENGL_N_glEvalMesh1 91
#define OPENGL_N_glEvalMesh2 92
#define OPENGL_N_glEvalPoint1 93
#define OPENGL_N_glEvalPoint2 94
#define OPENGL_N_glFeedbackBuffer 95
#define OPENGL_N_glFinish 96
#define OPENGL_N_glFlush 97
#define OPENGL_N_glFogf 98
#define OPENGL_N_glFogfv 99
#define OPENGL_N_glFogi 100
#define OPENGL_N_glFogiv 101
#define OPENGL_N_glFrontFace 102
#define OPENGL_N_glFrustum 103
#define OPENGL_N_glGenLists 104
#define OPENGL_N_glGenTextures 105
#define OPENGL_N_glGetBooleanv 106
#define OPENGL_N_glGetClipPlane 107
#define OPENGL_N_glGetDoublev 108
#define OPENGL_N_glGetError 109
#define OPENGL_N_glGetFloatv 110
#define OPENGL_N_glGetIntegerv 111
#define OPENGL_N_glGetLightfv 112
#define OPENGL_N_glGetLightiv 113
#define OPENGL_N_glGetMapdv 114
#define OPENGL_N_glGetMapfv 115
#define OPENGL_N_glGetMapiv 116
#define OPENGL_N_glGetMaterialfv 117
#define OPENGL_N_glGetMaterialiv 118
#define OPENGL_N_glGetPixelMapfv 119
#define OPENGL_N_glGetPixelMapuiv 120
#define OPENGL_N_glGetPixelMapusv 121
#define OPENGL_N_glGetPointerv 122
#define OPENGL_N_glGetPolygonStipple 123
#define OPENGL_N_glGetString 124
#define OPENGL_N_glGetTexEnvfv 125
#define OPENGL_N_glGetTexEnviv 126
#define OPENGL_N_glGetTexGendv 127
#define OPENGL_N_glGetTexGenfv 128
#define OPENGL_N_glGetTexGeniv 129
#define OPENGL_N_glGetTexImage 130
#define OPENGL_N_glGetTexLevelParameterfv 131
#define OPENGL_N_glGetTexLevelParameteriv 132
#define OPENGL_N_glGetTexParameterfv 133
#define OPENGL_N_glGetTexParameteriv 134
#define OPENGL_N_glHint 135
#define OPENGL_N_glIndexMask 136
#define OPENGL_N_glIndexPointer 137
#define OPENGL_N_glIndexd 138
#define OPENGL_N_glIndexdv 139
#define OPENGL_N_glIndexf 140
#define OPENGL_N_glIndexfv 141
#define OPENGL_N_glIndexi 142
#define OPENGL_N_glIndexiv 143
#define OPENGL_N_glIndexs 144
#define OPENGL_N_glIndexsv 145
#define OPENGL_N_glIndexub 146
#define OPENGL_N_glIndexubv 147
#define OPENGL_N_glInitNames 148
#define OPENGL_N_glInterleavedArrays 149
#define OPENGL_N_glIsEnabled 150
#define OPENGL_N_glIsList 151
#define OPENGL_N_glIsTexture 152
#define OPENGL_N_glLightModelf 153
#define OPENGL_N_glLightModelfv 154
#define OPENGL_N_glLightModeli 155
#define OPENGL_N_glLightModeliv 156
#define OPENGL_N_glLightf 157
#define OPENGL_N_glLightfv 158
#define OPENGL_N_glLighti 159
#define OPENGL_N_glLightiv 160
#define OPENGL_N_glLineStipple 161
#define OPENGL_N_glLineWidth 162
#define OPENGL_N_glListBase 163
#define OPENGL_N_glLoadIdentity 164
#define OPENGL_N_glLoadMatrixd 165
#define OPENGL_N_glLoadMatrixf 166
#define OPENGL_N_glLoadName 167
#define OPENGL_N_glLogicOp 168
#define OPENGL_N_glMap1d 169
#define OPENGL_N_glMap1f 170
#define OPENGL_N_glMap2d 171
#define OPENGL_N_glMap2f 172
#define OPENGL_N_glMapGrid1d 173
#define OPENGL_N_glMapGrid1f 174
#define OPENGL_N_glMapGrid2d 175
#define OPENGL_N_glMapGrid2f 176
#define OPENGL_N_glMaterialf 177
#define OPENGL_N_glMaterialfv 178
#define OPENGL_N_glMateriali 179
#define OPENGL_N_glMaterialiv 180
#define OPENGL_N_glMatrixMode 181
#define OPENGL_N_glMultMatrixd 182
#define OPENGL_N_glMultMatrixf 183
#define OPENGL_N_glNewList 184
#define OPENGL_N_glNormal3b 185
#define OPENGL_N_glNormal3bv 186
#define OPENGL_N_glNormal3d 187
#define OPENGL_N_glNormal3dv 188
#define OPENGL_N_glNormal3f 189
#define OPENGL_N_glNormal3fv 190
#define OPENGL_N_glNormal3i 191
#define OPENGL_N_glNormal3iv 192
#define OPENGL_N_glNormal3s 193
#define OPENGL_N_glNormal3sv 194
#define OPENGL_N_glNormalPointer 195
#define OPENGL_N_glOrtho 196
#define OPENGL_N_glPassThrough 197
#define OPENGL_N_glPixelMapfv 198
#define OPENGL_N_glPixelMapuiv 199
#define OPENGL_N_glPixelMapusv 200
#define OPENGL_N_glPixelStoref 201
#define OPENGL_N_glPixelStorei 202
#define OPENGL_N_glPixelTransferf 203
#define OPENGL_N_glPixelTransferi 204
#define OPENGL_N_glPixelZoom 205
#define OPENGL_N_glPointSize 206
#define OPENGL_N_glPolygonMode 207
#define OPENGL_N_glPolygonOffset 208
#define OPENGL_N_glPolygonStipple 209
#define OPENGL_N_glPopAttrib 210
#define OPENGL_N_glPopClientAttrib 211
#define OPENGL_N_glPopMatrix 212
#define OPENGL_N_glPopName 213
#define OPENGL_N_glPrioritizeTextures 214
#define OPENGL_N_glPushAttrib 215
#define OPENGL_N_glPushClientAttrib 216
#define OPENGL_N_glPushMatrix 217
#define OPENGL_N_glPushName 218
#define OPENGL_N_glRasterPos2d 219
#define OPENGL_N_glRasterPos2dv 220
#define OPENGL_N_glRasterPos2f 221
#define OPENGL_N_glRasterPos2fv 222
#define OPENGL_N_glRasterPos2i 223
#define OPENGL_N_glRasterPos2iv 224
#define OPENGL_N_glRasterPos2s 225
#define OPENGL_N_glRasterPos2sv 226
#define OPENGL_N_glRasterPos3d 227
#define OPENGL_N_glRasterPos3dv 228
#define OPENGL_N_glRasterPos3f 229
#define OPENGL_N_glRasterPos3fv 230
#define OPENGL_N_glRasterPos3i 231
#define OPENGL_N_glRasterPos3iv 232
#define OPENGL_N_glRasterPos3s 233
#define OPENGL_N_glRasterPos3sv 234
#define OPENGL_N_glRasterPos4d 235
#define OPENGL_N_glRasterPos4dv 236
#define OPENGL_N_glRasterPos4f 237
#define OPENGL_N_glRasterPos4fv 238
#define OPENGL_N_glRasterPos4i 239
#define OPENGL_N_glRasterPos4iv 240
#define OPENGL_N_glRasterPos4s 241
#define OPENGL_N_glRasterPos4sv 242
#define OPENGL_N_glReadBuffer 243
#define OPENGL_N_glReadPixels 244
#define OPENGL_N_glRectd 245
#define OPENGL_N_glRectdv 246
#define OPENGL_N_glRectf 247
#define OPENGL_N_glRectfv 248
#define OPENGL_N_glRecti 249
#define OPENGL_N_glRectiv 250
#define OPENGL_N_glRects 251
#define OPENGL_N_glRectsv 252
#define OPENGL_N_glRenderMode 253
#define OPENGL_N_glRotated 254
#define OPENGL_N_glRotatef 255
#define OPENGL_N_glScaled 256
#define OPENGL_N_glScalef 257
#define OPENGL_N_glScissor 258
#define OPENGL_N_glSelectBuffer 259
#define OPENGL_N_glShadeModel 260
#define OPENGL_N_glStencilFunc 261
#define OPENGL_N_glStencilMask 262
#define OPENGL_N_glStencilOp 263
#define OPENGL_N_glTexCoord1d 264
#define OPENGL_N_glTexCoord1dv 265
#define OPENGL_N_glTexCoord1f 266
#define OPENGL_N_glTexCoord1fv 267
#define OPENGL_N_glTexCoord1i 268
#define OPENGL_N_glTexCoord1iv 269
#define OPENGL_N_glTexCoord1s 270
#define OPENGL_N_glTexCoord1sv 271
#define OPENGL_N_glTexCoord2d 272
#define OPENGL_N_glTexCoord2dv 273
#define OPENGL_N_glTexCoord2f 274
#define OPENGL_N_glTexCoord2fv 275
#define OPENGL_N_glTexCoord2i 276
#define OPENGL_N_glTexCoord2iv 277
#define OPENGL_N_glTexCoord2s 278
#define OPENGL_N_glTexCoord2sv 279
#define OPENGL_N_glTexCoord3d 280
#define OPENGL_N_glTexCoord3dv 281
#define OPENGL_N_glTexCoord3f 282
#define OPENGL_N_glTexCoord3fv 283
#define OPENGL_N_glTexCoord3i 284
#define OPENGL_N_glTexCoord3iv 285
#define OPENGL_N_glTexCoord3s 286
#define OPENGL_N_glTexCoord3sv 287
#define OPENGL_N_glTexCoord4d 288
#define OPENGL_N_glTexCoord4dv 289
#define OPENGL_N_glTexCoord4f 290
#define OPENGL_N_glTexCoord4fv 291
#define OPENGL_N_glTexCoord4i 292
#define OPENGL_N_glTexCoord4iv 293
#define OPENGL_N_glTexCoord4s 294
#define OPENGL_N_glTexCoord4sv 295
#define OPENGL_N_glTexCoordPointer 296
#define OPENGL_N_glTexEnvf 297
#define OPENGL_N_glTexEnvfv 298
#define OPENGL_N_glTexEnvi 299
#define OPENGL_N_glTexEnviv 300
#define OPENGL_N_glTexGend 301
#define OPENGL_N_glTexGendv 302
#define OPENGL_N_glTexGenf 303
#define OPENGL_N_glTexGenfv 304
#define OPENGL_N_glTexGeni 305
#define OPENGL_N_glTexGeniv 306
#define OPENGL_N_glTexImage1D 307
#define OPENGL_N_glTexImage2D 308
#define OPENGL_N_glTexParameterf 309
#define OPENGL_N_glTexParameterfv 310
#define OPENGL_N_glTexParameteri 311
#define OPENGL_N_glTexParameteriv 312
#define OPENGL_N_glTexSubImage1D 313
#define OPENGL_N_glTexSubImage2D 314
#define OPENGL_N_glTranslated 315
#define OPENGL_N_glTranslatef 316
#define OPENGL_N_glVertex2d 317
#define OPENGL_N_glVertex2dv 318
#define OPENGL_N_glVertex2f 319
#define OPENGL_N_glVertex2fv 320
#define OPENGL_N_glVertex2i 321
#define OPENGL_N_glVertex2iv 322
#define OPENGL_N_glVertex2s 323
#define OPENGL_N_glVertex2sv 324
#define OPENGL_N_glVertex3d 325
#define OPENGL_N_glVertex3dv 326
#define OPENGL_N_glVertex3f 327
#define OPENGL_N_glVertex3fv 328
#define OPENGL_N_glVertex3i 329
#define OPENGL_N_glVertex3iv 330
#define OPENGL_N_glVertex3s 331
#define OPENGL_N_glVertex3sv 332
#define OPENGL_N_glVertex4d 333
#define OPENGL_N_glVertex4dv 334
#define OPENGL_N_glVertex4f 335
#define OPENGL_N_glVertex4fv 336
#define OPENGL_N_glVertex4i 337
#define OPENGL_N_glVertex4iv 338
#define OPENGL_N_glVertex4s 339
#define OPENGL_N_glVertex4sv 340
#define OPENGL_N_glVertexPointer 341
#define OPENGL_N_glViewport 342
#define OPENGL_N_wglChoosePixelFormat 343
#define OPENGL_N_wglCopyContext 344
#define OPENGL_N_wglCreateContext 345
#define OPENGL_N_wglCreateLayerContext 346
#define OPENGL_N_wglDeleteContext 347
#define OPENGL_N_wglDescribeLayerPlane 348
#define OPENGL_N_wglDescribePixelFormat 349
#define OPENGL_N_wglGetCurrentContext 350
#define OPENGL_N_wglGetCurrentDC 351
#define OPENGL_N_wglGetDefaultProcAddress 352
#define OPENGL_N_wglGetLayerPaletteEntries 353
#define OPENGL_N_wglGetPixelFormat 354
#define OPENGL_N_wglGetProcAddress 355
#define OPENGL_N_wglMakeCurrent 356
#define OPENGL_N_wglRealizeLayerPalette 357
#define OPENGL_N_wglSetLayerPaletteEntries 358
#define OPENGL_N_wglSetPixelFormat 359
#define OPENGL_N_wglShareLists 360
#define OPENGL_N_wglSwapBuffers 361
#define OPENGL_N_wglSwapLayerBuffers 362
#define OPENGL_N_wglSwapMultipleBuffers 363
#define OPENGL_N_wglUseFontBitmapsA 364
#define OPENGL_N_wglUseFontBitmapsW 365
#define OPENGL_N_wglUseFontOutlinesA 366
#define OPENGL_N_wglUseFontOutlinesW 367
#endif
