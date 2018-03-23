#include <windows.h>

#include "lua-functions.h"
#include "utils.h"
#include "sdl-utils.h"

#include <SDL.h>
#include "sdl2.h"
#include "opengl32.h"

DECLARE_HOOK_SDL(SDL_GL_SwapWindow, void, (SDL_Window * window));
DECLARE_HOOK_SDL(SDL_PollEvent, int, (SDL_Event *evt));

DECLARE_HOOK_OPENGL(glBindTexture, void, (GLenum target, GLuint texture));
DECLARE_HOOK_OPENGL(glTexCoord2f, void, (GLfloat s, GLfloat t));
DECLARE_HOOK_OPENGL(glTexImage2D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels));

void setupHooks() {
	sdl2Table[SDL_N_SDL_GL_SwapWindow] = (FARPROC) &SDL_GL_SwapWindow;
	sdl2Table[SDL_N_SDL_PollEvent] = (FARPROC) &SDL_PollEvent;

	opengl32Table[OPENGL_N_glBindTexture] = (FARPROC) &glBindTexture;
	opengl32Table[OPENGL_N_glTexCoord2f] = (FARPROC) &glTexCoord2f;
	opengl32Table[OPENGL_N_glTexImage2D] = (FARPROC) &glTexImage2D;
}

#define SDL_GL_SwapWindow hook_SDL_GL_SwapWindow
#define SDL_PollEvent hook_SDL_PollEvent
#define glBindTexture hook_glBindTexture
#define glTexCoord2f hook_glTexCoord2f
#define glTexImage2D hook_glTexImage2D

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID);
#ifdef main
#undef main
#endif

int index = 0;

void bail(lua_State *L, char *msg) {
	log("\nFATAL ERROR:\n  %s: %s\n\n", msg, lua_tostring(L, -1));
	exit(1);
}

SDL_Window *globalWindow;

GLuint texture;
void render() {
	int w, h;
	SDL_GL_GetDrawableSize(globalWindow, &w, &h);

	GLfloat mat[16];

	float r = (float) rand() / (float) RAND_MAX;
	glClearColor(sinf(0.0015f * SDL_GetTicks()) / 2 + 0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glPushMatrix();
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glOrtho(0.0, w, h, 0.0, -1.0, 1.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glMatrixMode(GL_MODELVIEW);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glPushMatrix();

	glLoadIdentity();
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glBegin(GL_QUADS);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glTexCoord2f(0, 0); glVertex2f(100, 100);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glTexCoord2f(0, 1); glVertex2f(100, 200);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glTexCoord2f(1, 1); glVertex2f(200, 200);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glTexCoord2f(1, 0); glVertex2f(200, 100);
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
	DllMain(NULL, DLL_PROCESS_ATTACH, NULL);

	setupHooks();

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	globalWindow = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
	SDL_GLContext gl_context = SDL_GL_CreateContext(globalWindow);

	SDL::Surface surface("test-tr.png");
	texture = surface.texture();

	lua_State *L = lua_open();

	installAutoexec(L);

	bool quitting = false;
	while(!quitting) {

		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				quitting = true;
			}
			if(event.type == SDL_MOUSEBUTTONUP) {
				SDL_ShowCursor(0);
				if(luaL_loadfile(L, "test.lua"))
					bail(L, "luaL_loadfile() failed");

				if(lua_pcall(L, 0, 0, 0))
					bail(L, "lua_pcall() failed");

				SDL_ShowCursor(1);
			}
		}

		SDL_GL_MakeCurrent(globalWindow, gl_context);

		render();

		SDL_GL_SwapWindow(globalWindow);

		SDL_Delay(2);
	}

	lua_close(L);

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(globalWindow);
	SDL_Quit();

	exit(0);

}
