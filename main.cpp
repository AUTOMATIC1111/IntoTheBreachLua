#include <windows.h>

#include "lua-functions.h"
#include "utils.h"
#include "sdl-utils.h"

#include <SDL.h>

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
	float r = (float) rand() / (float) RAND_MAX;
	glClearColor(sinf(0.0015f * SDL_GetTicks()) / 2 + 0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 640, 480, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 100, 0);
	glTexCoord2f(1, 1); glVertex3f(100, 100, 0);
	glTexCoord2f(1, 0); glVertex3f(100, 0, 0);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char *argv[]) {
	DllMain(NULL, DLL_PROCESS_ATTACH, NULL);

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	globalWindow = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext gl_context = SDL_GL_CreateContext(globalWindow);

	SDL::Surface surface("test-tr.png");
	texture = SDL::glTexture(surface.surface);

	bool quitting = false;
	while(!quitting) {

		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				quitting = true;
			}
			if(event.type == SDL_MOUSEBUTTONUP) {
				SDL_ShowCursor(0);

				lua_State *L = lua_open();

				installAutoexec(L);

				if(luaL_loadfile(L, "test.lua"))
					bail(L, "luaL_loadfile() failed");

				if(lua_pcall(L, 0, 0, 0))
					bail(L, "lua_pcall() failed");

				lua_close(L);

				SDL_ShowCursor(1);
			}
		}


		SDL_GL_MakeCurrent(globalWindow, gl_context);

		render();

		SDL_GL_SwapWindow(globalWindow);

		SDL_Delay(2);
	}

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(globalWindow);
	SDL_Quit();

	exit(0);

}
