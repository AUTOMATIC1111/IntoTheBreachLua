#ifndef __SDL_UTILS__
#define __SDL_UTILS__

#include <windows.h>
#include <SDL.h>
#include <string>
#include <memory>
#include "Gdiplus.h"

namespace SDL {

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

	TextSettings() {
		antialias = true;
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

	void setBitmap(Gdiplus::Bitmap *bitmap);
	void setBitmap(HBITMAP hbitmap, int x, int y, int w, int h);
	void setBitmap(void *data, int x, int y, int w, int h, int stride);

	void init();
	Surface(HWND hwnd);
	Surface(const std::string &filename);
	Surface(Surface *parent, int levels, Color *color);
	Surface(const Font * font, const TextSettings *settings, const std::string &text);

	int w() {
		if(surface == NULL) return 0;
		return surface->w;
	}

	int h() {
		if(surface == NULL) return 0;
		return surface->h;
	}

	~Surface();
};


struct Screen {
	std::unique_ptr<Surface> screenshot;
	SDL_Window* window;
	SDL_Surface* surface;

	Screen();

	int w() {
		return surface->w;
	}

	int h() {
		return surface->h;
	}

	void update();

	void blitRect(Surface *src, Rect *srcRect, Rect *destRect);
	void blit(Surface *src, Rect *srcRect, int destx, int desty);
	void drawrect(Color *color, Rect *rect);
	void clip(Rect *rect);
	void unclip();
};

struct EventLoop {
	SDL_Event event;

	bool next();
	int type();

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
