#include <windows.h>

#include "utils.h"
#include "lua5.1.h"
#include "sdl2.h"
#include "opengl32.h"
#include "SDL.h"

#include "sdl-utils.h"

#include <GL/GL.h>
#include <GL/GLU.h>
#include "glext.h"
#include "xxhash.h"

HOOK_SDL(SDL_GL_SwapWindow, void, (SDL_Window * window)) {
	if(! SDL::hookListDraw.empty()) {
		SDL::Screen screen;

		screen.begin();

		for(SDL::DrawHook *hook: SDL::hookListDraw) {
			hook->draw(screen);
		}

		screen.finishWithoutSwapping();
	}

	SDL::lastFrameMap.clear();
	return (*dll_SDL_GL_SwapWindow)(window);
}

HOOK_SDL(SDL_PollEvent, int, (SDL_Event *evt)) {
	if(SDL::hookListEvents.empty()) {
		return (*dll_SDL_PollEvent)(evt);
	}

	while(1) {
		int ret = (*dll_SDL_PollEvent)(evt);
		if(ret == 0) return 0;

		SDL::Event eventObject;
		eventObject.event = *evt;

		bool handled = false;
		for(SDL::EventHook *hook : SDL::hookListEvents) {
			if(hook->handle(eventObject)) {
				handled = true;
				break;
			}
		}

		if(!handled) {
			return 1;
		}
	}
}


static GLuint currentBoundTexture;
static GLuint currentUsedTexture;

HOOK_OPENGL(glBindTexture, void, (GLenum target, GLuint texture)) {
	if(target == GL_TEXTURE_2D) {
		currentBoundTexture = texture;
	}
		
	return (*dll_glBindTexture)(target, texture);
}

HOOK_OPENGL(glTexCoord2f, void, (GLfloat s, GLfloat t)) {
	if(currentUsedTexture != currentBoundTexture) {
		currentUsedTexture = currentUsedTexture;

		auto iter = SDL::texturesMap.find(currentBoundTexture);
		if(iter != SDL::texturesMap.end()) {
			unsigned long long hash = iter->second;
			SDL::lastFrameMap[hash] = 1;
		}
	}
	
	return (*dll_glTexCoord2f)(s, t);
}

HOOK_OPENGL(glTexImage2D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)) {
	if(format == 6408) {
		unsigned long long const hash = XXH64(pixels, width * height * 4, 0);
		SDL::texturesMap[currentBoundTexture] = hash;
	}
	
	return (*dll_glTexImage2D)(target, level, internalformat, width, height, border, format, type, pixels);
}
