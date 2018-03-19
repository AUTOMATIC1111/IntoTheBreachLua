#include "sdl-utils.h"
#include "utils.h"
#include "xxhash.h"
#include <algorithm>

#include "SDL_syswm.h"
#include "Gdiplus.h"
#pragma comment(lib,"Gdiplus.lib")

#include <GL/GL.h>
#include <GL/GLU.h>
#include "glext.h"
#pragma comment(lib,"opengl32.lib")

struct GdiPlusHelper {
	GdiPlusHelper() {
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
} gdiPlusHelper;

extern SDL_Window *globalWindow;

namespace SDL {

std::vector< DrawHook * > hookListDraw;
std::vector< EventHook * > hookListEvents;
std::map< GLuint, unsigned long long > texturesMap;
std::map< unsigned long long, int > lastFrameMap;

GLuint glTexture(SDL_Surface *_surface) {
	GLuint texture = 0;

	GLenum texture_format, internal_format, tex_type;
	texture_format = GL_RGBA;
	tex_type = GL_UNSIGNED_INT_8_8_8_8_REV;
	internal_format = GL_RGBA8;

	int alignment = 8;
	while(_surface->pitch%alignment) alignment >>= 1; // x%1==0 for any x
	glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

	int expected_pitch = (_surface->w*_surface->format->BytesPerPixel + alignment - 1) / alignment*alignment;
	if(_surface->pitch - expected_pitch >= alignment) // Alignment alone wont't solve it now
		glPixelStorei(GL_UNPACK_ROW_LENGTH, _surface->pitch / _surface->format->BytesPerPixel);
	else glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, _surface->w, _surface->h, 0, texture_format, tex_type, _surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

	return texture;
}

Color::Color() {
	r = 255;
	g = 255;
	b = 255;
	a = 255;
}

Color::Color(int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 0xff;
}

Rect::Rect(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Font::Font() {
	defaults();
}
void Font::defaults() {
	font.reset(new Gdiplus::Font(L"Arial", 12));
}

Font::Font(const std::string &name, double size) {
	font.reset(new Gdiplus::Font(s2ws(name).c_str(), (Gdiplus::REAL) size, Gdiplus::UnitPoint));
}

FileFont::FileFont(const std::string &filename, double size) {
	privateFontCollection.AddFontFile(s2ws(filename).c_str());
	int count = privateFontCollection.GetFamilyCount();

	int found = 0;
	Gdiplus::FontFamily family;
	privateFontCollection.GetFamilies(1, &family, &found);
	if(found < 1) {
		defaults();
		return;
	}

	WCHAR familyName[LF_FACESIZE];
	family.GetFamilyName(familyName);
	Gdiplus::Font* newfont = new Gdiplus::Font(
		familyName, (Gdiplus::REAL) size, Gdiplus::FontStyleRegular, Gdiplus::UnitPoint, &privateFontCollection
	);
	font.reset(newfont);
}

void Surface::init() {
	pixelData = NULL;
	surface = NULL;
	textureId = 0;
	hash = 0;
}

Surface::~Surface() {
	if(pixelData != NULL)
		delete[] pixelData;
	if(surface != NULL)
		SDL_FreeSurface(surface);
	if(textureId != 0)
		glDeleteTextures(1, &textureId);
}

void Surface::setBitmap(HBITMAP hCaptureBitmap, int sx, int sy, int w, int h) {
	BITMAP bm;

	GetObject(hCaptureBitmap, sizeof(BITMAP), &bm);

	int nScreenWidth = bm.bmWidth;
	int nScreenHeight = bm.bmHeight;

	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = nScreenWidth;
	bmpInfo.bmiHeader.biHeight = -nScreenHeight;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = 0;

	HDC hCaptureDC = CreateCompatibleDC(NULL);
	unsigned char *pixels = new unsigned char[nScreenWidth * nScreenHeight * 4];
	::GetDIBits(hCaptureDC, hCaptureBitmap, 0, nScreenHeight, pixels, &bmpInfo, DIB_RGB_COLORS);

	setBitmap(pixels, sx, sy, w, h, nScreenWidth * 4);

	delete[] pixels;

	DeleteDC(hCaptureDC);
}

void Surface::setBitmap(void *data, int sx, int sy, int w, int h, int stride) {
	unsigned char *pixels = (unsigned char *) data;

	pixelData = new unsigned char[w * h * 4];
	int initial = 0;
	if(stride < 0) {
		initial = (sy + h - 1) * -stride;
	}

	for(int y = 0; y < h; y++) {
		unsigned char *dst = &pixelData[y*w * 4];
		unsigned char *src = &pixels[initial + sx * 4 + (sy + y) * stride];

		for(int x = 0; x < w; x++) {
			dst[0] = src[2];
			dst[1] = src[1];
			dst[2] = src[0];
			dst[3] = src[3];

			dst += 4;
			src += 4;
		}
	}

	hash = XXH64(pixelData, w * h * 4, 0);

	Uint32 rmask = 0x000000ff;
	Uint32 gmask = 0x0000ff00;
	Uint32 bmask = 0x00ff0000;
	Uint32 amask = 0xff000000;
	surface = SDL_CreateRGBSurfaceFrom((void*) pixelData, w, h, 32, 4 * w, rmask, gmask, bmask, amask);

	if(surface == NULL) {
		::log("Creating surface from bitmap failed: %s", SDL_GetError());
		exit(1);
	}
}

void Surface::setBitmap(Gdiplus::Bitmap *bitmap) {
	Gdiplus::BitmapData* bitmapData = new Gdiplus::BitmapData;
	Gdiplus::Rect rect(0, 0, bitmap->GetWidth(), bitmap->GetHeight());

	bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, bitmapData);
	UINT* pixels = (UINT*) bitmapData->Scan0;

	setBitmap(pixels, 0, 0, rect.Width, rect.Height, bitmapData->Stride);

	bitmap->UnlockBits(bitmapData);

	delete bitmapData;
}

Surface::Surface(const std::string &filename) {
	init();

	std::wstring ws = s2ws(filename);
	Gdiplus::Bitmap *bitmap = Gdiplus::Bitmap::FromFile(ws.c_str(), false);
	if(bitmap == NULL) {
		::log("couldn't open picture: %s\n", filename.c_str());
		exit(1);
	}

	setBitmap(bitmap);

	delete bitmap;
}

Surface::Surface(const Font * font, const TextSettings *settings, const std::string &text) {
	init();
	int outline = settings->outlineWidth;
	bool antialias = (settings == NULL || settings->antialias) && outline==0;

	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetDC(hDesktopWnd);
	HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);

	Gdiplus::Graphics graphics(hCaptureDC);
	std::wstring s = s2ws(text);
	Gdiplus::RectF layoutRect(0, 0, 2560, 1600);
	Gdiplus::RectF boundRect;

	graphics.MeasureString(s.c_str(), -1, *font, layoutRect, &boundRect);

	Gdiplus::Color color = settings == NULL ?
		Gdiplus::Color::White :
		Gdiplus::Color::MakeARGB(settings->color.a, settings->color.r, settings->color.g, settings->color.b);

	boundRect.Height = font->font->GetHeight(&graphics) + outline * 2;
	boundRect.Width += outline * 2;

	Gdiplus::Bitmap bitmap((int) ceil(boundRect.Width), (int) ceil(boundRect.Height), PixelFormat32bppARGB);
	Gdiplus::Graphics *g = Gdiplus::Graphics::FromImage(&bitmap);
	Gdiplus::SolidBrush brush(color);

	g->SetTextRenderingHint(antialias ?
							Gdiplus::TextRenderingHintAntiAlias :
							Gdiplus::TextRenderingHintSingleBitPerPixelGridFit
	);
	g->DrawString(s.c_str(), -1, *font, Gdiplus::PointF((Gdiplus::REAL) outline, (Gdiplus::REAL) outline), &brush);
	delete g;
	
	setBitmap(&bitmap);

	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);

	addOutline(outline, &settings->outlineColor);
}

void Surface::addOutline(int levels, const Color *color) {
	if(levels == 0) return;

	int colorValue = (0xff << 24) | (color->r << 16) | (color->g << 8) | (color->b);

	int w = surface->w;
	int h = surface->h;

	unsigned char *data = new unsigned char[w * h * 4];
	unsigned char *data2 = new unsigned char[w * h * 4];

	SDL_LockSurface(surface);
	memcpy(data, surface->pixels, 4 * w * h);

	for(int i = 0; i < levels; i++) {
		memcpy(data2, data, 4 * w * h);

		for(int y = 0; y < h; y++) {
			for(int x = 0; x < w; x++) {
				unsigned char *p = &data[(x + y * w) * 4];
				unsigned char *p2 = &data2[(x + y * w) * 4];
				if(p[3] > 128) {
					if(x > 0 && p[-1] < 128)    ((int *) p2)[-1] = colorValue;
					if(x + 1 < w && p[7] < 128) ((int *) p2)[+1] = colorValue;
				}
			}
		}

		memcpy(data, data2, 4 * w * h);

		for(int y = 0; y < h; y++) {
			for(int x = 0; x < w; x++) {
				unsigned char *p = &data[(x + y * w) * 4];
				unsigned char *p2 = &data2[(x + y * w) * 4];
				if(p[3] > 128) {
					if(y > 0 && p[-w * 4 + 3] < 128)    ((int *) p2)[-w] = colorValue;
					if(y + 1 < h && p[w * 4 + 3] < 128) ((int *) p2)[+w] = colorValue;
				}
			}
		}

		unsigned char *tmp = data;
		data = data2;
		data2 = tmp;
	}

	memcpy(surface->pixels, data, 4 * w * h);
	SDL_UnlockSurface(surface);

	delete[] data;
	delete[] data2;
}

Surface::Surface(Surface *parent, int levels, Color *color) {
	init();

	int w = parent->w();
	int h = parent->h();

	unsigned char *data = new unsigned char[w * h * 4];

	SDL_LockSurface(parent->surface);
	memcpy(data, parent->surface->pixels, 4 * w * h);
	SDL_UnlockSurface(parent->surface);

	setBitmap(data, 0, 0, w, h, w * 4);

	delete[] data;

	addOutline(levels, color);
}

Surface::Surface(int scaling, Surface *parent) {
	init();

	int w = parent->w();
	int h = parent->h();

	int neww = w * scaling;
	int newh = h * scaling;

	Uint32 *data = new Uint32[neww * newh];

	SDL_LockSurface(parent->surface);
	Uint32 *pixels = (Uint32 *) parent->pixelData;

	for(int x = 0; x < w; x++) {
		for(int y = 0; y < h; y++) {
			Uint32 pixel = pixels[x + y * w];
			for(int x1 = 0; x1 < scaling; x1++) {
				for(int y1 = 0; y1 < scaling; y1++) {
					data[(x * scaling + x1) + (y * scaling + y1) * neww] = pixel;
				}
			}
		}
	}

	SDL_UnlockSurface(parent->surface);

	setBitmap(data, 0, 0, neww, newh, neww * 4);

	delete[] data;
}
Surface::Surface() {
	init();
}

bool Surface::wasDrawn() {
	return lastFrameMap.find(hash) != lastFrameMap.end();
}

SurfaceScreenshot::SurfaceScreenshot() {
	SDL_Window *window = SDL_GL_GetCurrentWindow();
	if(window == NULL) window = globalWindow;

	int w, h;
	SDL_GL_GetDrawableSize(window, &w, &h);

	unsigned char* pixels = new unsigned char[4 * w * h];
	glReadPixels(0, 0, w, h, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

	setBitmap(pixels, 0, 0, w, h, -w * 4);

	delete pixels;
};

Screen::Screen() {
	window = SDL_GL_GetCurrentWindow();
	if(window == NULL) window = globalWindow;
}

void Screen::begin() {
	int w, h;
	SDL_GL_GetDrawableSize(window, &w, &h);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, w, h, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Screen::finishWithoutSwapping() {
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}

void Screen::finish() {
	finishWithoutSwapping();
	SDL_GL_SwapWindow(window);
}

void Screen::blitRect(Surface *src, Rect *srcRect, Rect *destRect) {
	if(src == NULL) return;

	int x1 = destRect->x;
	int y1 = destRect->y;
	int x2 = destRect->x + destRect->w;
	int y2 = destRect->y + destRect->h;

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, src->texture());

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3i(x1, y1, 0);
	glTexCoord2f(0, 1); glVertex3i(x1, y2, 0);
	glTexCoord2f(1, 1); glVertex3i(x2, y2, 0);
	glTexCoord2f(1, 0); glVertex3i(x2, y1, 0);
	glEnd();
}

void Screen::blit(Surface *src, Rect *srcRect, int destx, int desty) {
	if(src == NULL) return;
	
	Rect destRect = { destx, desty, src->w(), src->h() };

	blitRect(src, srcRect, &destRect);
}
void Screen::drawrect(Color *color, Rect *rect) {
	glColor4f(color->r/255.0f, color->g / 255.0f, color->b / 255.0f, color->a / 255.0f);
	glDisable(GL_TEXTURE_2D);

	int x1, y1, x2, y2;
	if(rect == NULL) {
		int w, h;
		SDL_GL_GetDrawableSize(window, &w, &h);

		x1 = 0;
		y1 = 0;
		x2 = w;
		y2 = h;
	} else {
		x1 = rect->x;
		y1 = rect->y;
		x2 = rect->x + rect->w;
		y2 = rect->y + rect->h;
	}


	glBegin(GL_QUADS);
	glVertex3i(x1, y1, 0);
	glVertex3i(x1, y2, 0);
	glVertex3i(x2, y2, 0);
	glVertex3i(x2, y1, 0);
	glEnd();
}

void Screen::clip(Rect *rect) {
	clippingRects.push_back(*rect);

	applyClipping();
}

void Screen::unclip() {
	if(!clippingRects.empty())
		clippingRects.pop_back();
	
	applyClipping();
}

void Screen::applyClipping() {
	if(clippingRects.empty()) {
		glDisable(GL_SCISSOR_TEST);
	} else {
		int w, h;
		SDL_GL_GetDrawableSize(window, &w, &h);

		Rect *rect = &clippingRects.at(clippingRects.size() - 1);
		glScissor(rect->x, h - rect->y - rect->h, rect->w, rect->h);
		glEnable(GL_SCISSOR_TEST);
	}
}

DrawHook::DrawHook() {
	hookListDraw.push_back(this);
}
DrawHook::~DrawHook() {
	hookListDraw.erase(std::remove(hookListDraw.begin(), hookListDraw.end(), this), hookListDraw.end());
}

EventHook::EventHook() {
	hookListEvents.push_back(this);
}
EventHook::~EventHook() {
	hookListEvents.erase(std::remove(hookListEvents.begin(), hookListEvents.end(), this), hookListEvents.end());
}

bool EventLoop::next() {
	if(SDL_PollEvent(&event) == 0)
		return false;

	return true;
}

int Event::type() {
	return event.type;
}

int Event::mousebutton() {
	return event.button.button;
}

int Event::x() {
	return event.motion.x;
}

int Event::y() {
	return event.motion.y;
}

int Event::wheely() {
	return event.wheel.y;
}
int Event::keycode() {
	return event.key.keysym.sym;
}






int mousex() {
	int x, y;
	SDL_GetMouseState(&x, &y);

	return x;
}

int mousey() {
	int x, y;
	SDL_GetMouseState(&x, &y);

	return y;
}

void log(const std::string & line) {
	::log("%s\n", line.c_str());
}

bool isshiftdown() {
	return (GetAsyncKeyState(VK_SHIFT) & 0x8000) == 0x8000;
}

Timer::Timer() {
	startTime = SDL_GetTicks();
}

int Timer::elapsed() {
	return SDL_GetTicks() - startTime;
}

}

