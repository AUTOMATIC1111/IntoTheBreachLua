#ifndef __SDL_UTILS__
#define __SDL_UTILS__

#include <windows.h>
#include <SDL.h>
#include <string>
#include <memory>
#include <vector>
#include "Gdiplus.h"

#include <GL/GL.h>
#include <GL/GLU.h>

namespace SDL {

GLuint glTexture(SDL_Surface *surface);

struct Color :public SDL_Color {
	Color();
	Color(int r, int g, int b, int a);
	Color(int r, int g, int b);
};

struct Rect :public SDL_Rect {
	Rect(int x, int y, int w, int h);
};

struct TextSettings {
	Color color;
	bool antialias;

	Color outlineColor;
	int outlineWidth;

	TextSettings() {
		antialias = true;
		outlineWidth = 0;
	}
};

struct Font {
	std::unique_ptr<Gdiplus::Font> font;

	Font();
	Font(const std::string &name, double size);

	void defaults();

	operator const Gdiplus::Font *() const {
		return font.get();
	}
};

struct FileFont :public Font {
	Gdiplus::PrivateFontCollection privateFontCollection;

	FileFont(const std::string &filename, double size);
};

struct Surface {
	unsigned char *pixelData;
	SDL_Surface* surface;
	GLuint textureId;

	void setBitmap(Gdiplus::Bitmap *bitmap);
	void setBitmap(HBITMAP hbitmap, int x, int y, int w, int h);
	void setBitmap(void *data, int x, int y, int w, int h, int stride);

	void init();
	Surface(HWND hwnd);
	Surface(const std::string &filename);
	Surface(Surface *parent, int levels, Color *color);
	Surface(const Font * font, const TextSettings *settings, const std::string &text);
	Surface(int scaling, Surface *parent);

	int w() {
		if(surface == NULL) return 0;
		return surface->w;
	}

	int h() {
		if(surface == NULL) return 0;
		return surface->h;
	}

	GLint texture() {
		if(textureId == 0 && surface != NULL) {
			textureId = glTexture(surface);
		}

		return textureId;
	}

	~Surface();

protected:
	void addOutline(int levels, const Color *color);
};

struct SurfaceScreenshot :public Surface {
	SurfaceScreenshot();
};

struct Screen {
	SDL_Window* window;
	std::vector<Rect> clippingRects;

	Screen();

	int w() {
		int w, h;

		SDL_GL_GetDrawableSize(window, &w, &h);
		return w;
	}

	int h() {
		int w, h;

		SDL_GL_GetDrawableSize(window, &w, &h);
		return h;
	}

	void begin();
	void finish();

	void blitRect(Surface *src, Rect *srcRect, Rect *destRect);
	void blit(Surface *src, Rect *srcRect, int destx, int desty);
	void drawrect(Color *color, Rect *rect);
	void clip(Rect *rect);
	void unclip();

protected:

	void applyClipping();
};

struct EventLoop {
	SDL_Event event;

	bool next();
	int type();

	int mousebutton();
	int x();
	int y();

	int wheely();
	int keycode();
};

struct Timer {
	Timer();

	int startTime;

	int elapsed();
};

int mousex();
int mousey();

bool isshiftdown();

void log(const std::string & line);

}

#endif
