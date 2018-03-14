#include "lua-functions.h"
#include "utils.h"
#include <windows.h>
#include "sdl-utils.h"
#include "LuaBridge/LuaBridge.h"

using namespace luabridge;

#include <SDL.h>
#include "SDL_syswm.h"
#include <vector>
#include <algorithm>

int SdlTest(lua_State *L) {

	return 0;
}


int ListDirectoryFull(lua_State *L, int mode) {
	const char *dirname = lua_tostring(L, 1);

	lua_newtable(L);

	WIN32_FIND_DATAA fdFile;
	HANDLE handle = NULL;

	std::string path = format("%s\\*.*", dirname);
	if((handle = FindFirstFileA(path.c_str(), &fdFile)) == INVALID_HANDLE_VALUE) {
		return 1;
	}

	int index = 0;
	do {
		if(strcmp(fdFile.cFileName, ".") == 0 || strcmp(fdFile.cFileName, "..") == 0)
			continue;

		int isDir = fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? 1 : 0;
		if(mode != -1 && mode != isDir)
			continue;

		lua_pushnumber(L, index++);
		lua_pushstring(L, fdFile.cFileName);
		lua_settable(L, -3);

	} while(FindNextFileA(handle, &fdFile));

	FindClose(handle);

	return 1;
}

int ListDirectory(lua_State *L) {
	return ListDirectoryFull(L, -1);
}

int ListDirectoryFiles(lua_State *L) {
	return ListDirectoryFull(L, 0);
}

int ListDirectoryDirs(lua_State *L) {
	return ListDirectoryFull(L, 1);
}

int Messagebox(lua_State *L) {
	const char *text = lua_tostring(L, 1);

	MessageBoxA(NULL, text, "Message", 0);

	return 0;
}

namespace event{
	int quit = SDL_QUIT;
	int keydown = SDL_KEYDOWN;
	int keyup = SDL_KEYUP;
	int mousemotion = SDL_MOUSEMOTION;
	int mousebuttondown = SDL_MOUSEBUTTONDOWN;
	int mousebuttonup = SDL_MOUSEBUTTONUP;
	int mousewheel = SDL_MOUSEWHEEL;
}

void installFunctions(lua_State *L) {
	luaL_openlibs(L);
	
	getGlobalNamespace(L)
		.beginNamespace("sdl")

		.beginClass <SDL::Color>("color")
		.endClass()

		.deriveClass<SDL::Color, SDL::Color>("rgba")
		.addConstructor <void(*) (int r, int g, int b, int a)>()
		.endClass()

		.deriveClass<SDL::Color, SDL::Color>("rgb")
		.addConstructor <void(*) (int r, int g, int b)>()
		.endClass()

		.beginClass <SDL::TextSettings>("textsettings")
		.addConstructor <void(*) ()>()
		.addData("antialias", &SDL::TextSettings::antialias)
		.addData("color", &SDL::TextSettings::color)
		.endClass()

		.beginClass <SDL::Font>("font")
		.addConstructor <void(*) (const std::string & name, double size)>()
		.endClass()

		.deriveClass <SDL::FileFont, SDL::Font>("filefont")
		.addConstructor <void(*) (const std::string & name, double size)>()
		.endClass()

		.beginClass <SDL::Surface>("surface")
		.addConstructor <void(*) (const std::string & s)>()
		.addFunction("w", &SDL::Surface::w)
		.addFunction("h", &SDL::Surface::h)
		.endClass()

		.deriveClass<SDL::Surface, SDL::Surface>("text")
		.addConstructor <void(*) (const SDL::Font *, const SDL::TextSettings *settings, const std::string & s)>()
		.endClass()

		.deriveClass<SDL::Surface, SDL::Surface>("outlined")
		.addConstructor <void(*) (SDL::Surface *base, int levels, SDL::Color *color)>()
		.endClass()


		.beginClass <SDL::Screen>("screen")
		.addConstructor <void(*) ()>()
		.addFunction("w", &SDL::Screen::w)
		.addFunction("h", &SDL::Screen::h)
		.addFunction("update", &SDL::Screen::update)
		.addFunction("blit", &SDL::Screen::blit)
		.addFunction("drawrect", &SDL::Screen::drawrect)
		.addFunction("clip", &SDL::Screen::clip)
		.addFunction("unclip", &SDL::Screen::unclip)
		.endClass()

		.beginClass <SDL::EventLoop>("eventloop")
		.addConstructor <void(*) ()>()
		.addFunction("next", &SDL::EventLoop::next)
		.addFunction("type", &SDL::EventLoop::type)
		.addFunction("x", &SDL::EventLoop::x)
		.addFunction("y", &SDL::EventLoop::y)
		.addFunction("wheel", &SDL::EventLoop::wheely)
		.addFunction("keycode", &SDL::EventLoop::keycode)
		.addFunction("mousebutton", &SDL::EventLoop::mousebutton)
		.endClass()


		.beginClass <SDL::Rect>("rect")
		.addConstructor <void(*) (int, int, int, int)>()
		.addData("x", &SDL::Rect::x)
		.addData("y", &SDL::Rect::y)
		.addData("w", &SDL::Rect::w)
		.addData("h", &SDL::Rect::h)
		.endClass()

		.beginClass <SDL::Timer>("timer")
		.addConstructor <void(*) ()>()
		.addFunction("elapsed", &SDL::Timer::elapsed)
		.endClass()

		.beginNamespace("events")
		.addVariable("quit", &event::quit, false)
		.addVariable("keydown", &event::keydown, false)
		.addVariable("keyup", &event::keyup, false)
		.addVariable("mousemotion", &event::mousemotion, false)
		.addVariable("mousebuttondown", &event::mousebuttondown, false)
		.addVariable("mousebuttonup", &event::mousebuttonup, false)
		.addVariable("mousewheel", &event::mousewheel, false)
		.endNamespace()

		.beginNamespace("mouse")
		.addFunction("x", SDL::mousex)
		.addFunction("y", SDL::mousey)
		.endNamespace()

		.addFunction("log", SDL::log)

		.addFunction("isshiftdown", SDL::isshiftdown)
		
		.endNamespace();
}

void installAutoexec(lua_State *L) {
	std::vector<std::string> items;
	
	listDir("scripts/autoexec", [&](const std::string &filename, bool isDir) {
		if(!isDir) items.emplace_back(filename);
	});

	std::sort(items.begin(), items.end());
	for(const std::string & filename : items) {
		if(luaL_loadfile(L, filename.c_str()) == 0) {
			lua_pcall(L, 0, 0, 0);
		}
	}
}