#include "sdl-utils.h"
#include "utils.h"

#include "SDL_syswm.h"
#include "Gdiplus.h"
#pragma comment(lib,"Gdiplus.lib")

struct GdiPlusHelper {
	GdiPlusHelper() {
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}

} gdiPlusHelper;

extern SDL_Window *globalWindow;

namespace SDL {

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
}

Surface::~Surface() {
	if(pixelData != NULL)
		delete[] pixelData;
	if(surface != NULL)
		SDL_FreeSurface(surface);
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
	for(int y = 0; y < h; y++) {
		memcpy(&pixelData[y*w * 4], &pixels[sx * 4 + (sy + y) * stride], 4 * w);
	}

	Uint32 rmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00;
	Uint32 bmask = 0x000000ff;
	Uint32 amask = 0xff000000;
	surface = SDL_CreateRGBSurfaceFrom((void*) pixelData, w, h, 32, 4 * w, rmask, gmask, bmask, amask);

	if(surface == NULL) {
		::log("Creating surface from bitmap failed: %s", SDL_GetError());
		exit(1);
	}
}


Surface::Surface(HWND hwnd) {
	init();

	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetDC(hDesktopWnd);
	HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
	SelectObject(hCaptureDC, hCaptureBitmap);

	BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = nScreenWidth;
	bmi.bmiHeader.biHeight = -nScreenHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	RECT frame;
	POINT p = { 0, 0 };
	GetClientRect(hwnd, &frame);
	ClientToScreen(hwnd, &p);

	setBitmap(hCaptureBitmap, p.x, p.y, frame.right, frame.bottom);

	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);
	DeleteObject(hCaptureBitmap);
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

	boundRect.Height = font->font->GetHeight(&graphics);

	Gdiplus::Bitmap bitmap((int) ceil(boundRect.Width), (int) ceil(boundRect.Height), PixelFormat32bppARGB);
	Gdiplus::Graphics *g = Gdiplus::Graphics::FromImage(&bitmap);
	Gdiplus::SolidBrush brush(color);

	g->SetTextRenderingHint(settings && !settings->antialias ?
							Gdiplus::TextRenderingHintSingleBitPerPixelGridFit :
							Gdiplus::TextRenderingHintAntiAlias
	);
	g->DrawString(s.c_str(), -1, *font, Gdiplus::PointF(0, 0), &brush);
	delete g;

	setBitmap(&bitmap);

	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);
}

Surface::Surface(Surface *parent, int levels, Color *color) {
	init();

	int colorValue = (0xff << 24) | (color->r << 16) | (color->g << 8) | (color->b);

	int w = parent->w();
	int h = parent->h();

	unsigned char *data = new unsigned char[w * h * 4];
	unsigned char *data2 = new unsigned char[w * h * 4];

	SDL_LockSurface(parent->surface);
	memcpy(data, parent->surface->pixels, 4 * w * h);
	SDL_UnlockSurface(parent->surface);

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

	setBitmap(data, 0, 0, w, h, w*4);

	delete[] data;
	delete[] data2;
}

Screen::Screen() {
	window = SDL_GL_GetCurrentWindow();
	if(window == NULL) window = globalWindow;

	surface = SDL_GetWindowSurface(window);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);
	screenshot.reset(new Surface(wmInfo.info.win.window));

	SDL_BlitSurface(screenshot->surface, NULL, surface, NULL);
}

void Screen::update() {
	SDL_UpdateWindowSurface(window);
	SDL_BlitSurface(screenshot->surface, NULL, surface, NULL);
}

void Screen::blitRect(Surface *src, Rect *srcRect, Rect *destRect) {
	SDL_BlitSurface(src->surface, srcRect, surface, destRect);
}

void Screen::blit(Surface *src, Rect *srcRect, int destx, int desty) {
	Rect destRect = { destx, desty, src->w(), src->h() };

	SDL_BlitSurface(src->surface, srcRect, surface, &destRect);
}
void Screen::drawrect(Color *color, Rect *rect) {
	SDL_FillRect(surface, rect, SDL_MapRGBA(surface->format, color->r, color->g, color->b, color->a));
}

void Screen::clip(Rect *rect) {
	SDL_SetClipRect(surface, rect);
}

void Screen::unclip() {
	SDL_SetClipRect(surface, NULL);
}


bool EventLoop::next() {
	if(SDL_PollEvent(&event) == 0)
		return false;

	return true;
}

int EventLoop::type() {
	return event.type;
}

int EventLoop::x() {
	return event.motion.x;
}

int EventLoop::y() {
	return event.motion.y;
}

int EventLoop::wheely() {
	return event.wheel.y;
}
int EventLoop::keycode() {
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

