#include <windows.h>

#include "lua-functions.h"
#include "utils.h"
#include "sdl-utils.h"

#include <SDL.h>
#include "SDL_syswm.h"


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
int main(int argc, char **argv) {
	DllMain(NULL, DLL_PROCESS_ATTACH, NULL);

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = globalWindow = SDL_CreateWindow(
		"An SDL2 window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	if(window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

	bool quit = false;
	SDL_Event e;
	while(!quit) {
		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				quit = true;
			}
			if(e.type == SDL_MOUSEBUTTONUP) {
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

		int red = (int) (0xff * (sin(index*0.001) + 1) / 2);
		SDL_Rect rect = { 100,100,200,100 + red };
		SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, red, 0x80, 0x80));

		SDL_UpdateWindowSurface(window);
		index++;
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

