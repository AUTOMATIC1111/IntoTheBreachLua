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
	if(SDL::hookListEvents.empty() || evt==NULL) {
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

struct Tl {
	GLdouble x;
	GLdouble y;
};
std::vector<Tl> tlStack = { Tl {0, 0} };
GLenum matrixMode;

HOOK_OPENGL(glMatrixMode, void, (GLenum mode)) {
	matrixMode = mode;
	return (*dll_glMatrixMode)(mode);
}

HOOK_OPENGL(glPushMatrix, void, ()) {
	if(matrixMode == GL_MODELVIEW) {
		tlStack.push_back(tlStack.at(tlStack.size() - 1));
	}

	return (*dll_glPushMatrix)();
}

HOOK_OPENGL(glPopMatrix, void, ()) {
	if(matrixMode == GL_MODELVIEW && tlStack.size()>1) {
		tlStack.pop_back();
	}

	return (*dll_glPopMatrix)();
}

HOOK_OPENGL(glLoadIdentity, void, ()) {
	if(matrixMode == GL_MODELVIEW) {
		Tl &tl = tlStack.at(tlStack.size() - 1);
		tl.x = 0;
		tl.y = 0;
	}

	return (*dll_glLoadIdentity)();
}

HOOK_OPENGL(glTranslatef, void, (GLfloat x, GLfloat y, GLfloat z)) {
	if(matrixMode == GL_MODELVIEW) {
		Tl &tl = tlStack.at(tlStack.size() - 1);
		tl.x += x;
		tl.y += y;
	}

	(*dll_glTranslatef)(x, y, z);
}
HOOK_OPENGL(glScalef, void, (GLfloat x, GLfloat y, GLfloat z)) {
	return (*dll_glScalef)(x, y, z);
}

static std::map<unsigned long long, SDL::Coord *> coordsToBeFixed;
static int glVertex2fNum = 0;

HOOK_OPENGL(glVertex2f, void, (GLfloat x, GLfloat y)) {
	if(glVertex2fNum++ % 4 == 0) {
		if(currentUsedTexture != currentBoundTexture) {
			currentUsedTexture = currentUsedTexture;

			auto iter = SDL::texturesMap.find(currentBoundTexture);
			if(iter != SDL::texturesMap.end()) {
				unsigned long long hash = iter->second;
				SDL::Coord & coord = SDL::lastFrameMap[hash];
				Tl &tl = tlStack.at(tlStack.size() - 1);
				coord.x = x + tl.x;
				coord.y = y + tl.y;
			}
		}
	}

	return (*dll_glVertex2f)(x, y);
}

HOOK_OPENGL(glTexImage2D, void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)) {
	if(format == 6408) {
		unsigned long long const hash = XXH64(pixels, width * height * 4, 0);
		SDL::texturesMap[currentBoundTexture] = hash;
	}
	
	return (*dll_glTexImage2D)(target, level, internalformat, width, height, border, format, type, pixels);
}
