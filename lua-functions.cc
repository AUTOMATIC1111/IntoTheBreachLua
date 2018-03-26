#include "lua-functions.h"
#include "utils.h"
#include "os.h"
#include <windows.h>
#include "sdl-utils.h"
#include "LuaBridge/LuaBridge.h"

using namespace luabridge;

#include <SDL.h>
#include "SDL_syswm.h"
#include <vector>
#include <algorithm>

int listDirectoryFull(lua_State *L, int mode) {
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

int listDirectory(lua_State *L) {
	return listDirectoryFull(L, -1);
}

int listDirectoryFiles(lua_State *L) {
	return listDirectoryFull(L, 0);
}

int listDirectoryDirs(lua_State *L) {
	return listDirectoryFull(L, 1);
}

int messagebox(lua_State *L) {
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

struct DrawHook :public SDL::DrawHook {
	LuaRef ref;

	DrawHook(LuaRef r) :ref(r) {

	}

	void draw(SDL::Screen &screen) {
		try {
			ref(screen);
		} catch(luabridge::LuaException const& e) {
			panic(e.what());
		}
	}
};

struct EventHook :public SDL::EventHook {
	LuaRef ref;

	EventHook(LuaRef r) :ref(r) {

	}

	bool handle(SDL::Event &evt) {
		try {
			return ref(evt);
		} catch(luabridge::LuaException const& e) {
			panic(e.what());

			return false;
		}
	}
};

static std::vector<SDL::Color *> createColormapFromLua(LuaRef & r) {
	std::vector<SDL::Color *> res;
	
	try {
		for(int i = 1; i <= r.length(); i++) {
			SDL::Color *a = r[i].cast<SDL::Color *>();
			res.push_back(a);
		}
	} catch(luabridge::LuaException const& e) {
		panic(e.what());
	}

	return res;
}

struct SurfaceColorMapped :public SDL::Surface {
	SurfaceColorMapped(SDL::Surface *parent, LuaRef r) :SDL::Surface(parent, createColormapFromLua(r)) {
	
	}
};

void installFunctions(lua_State *L) {
	luaL_openlibs(L);

	getGlobalNamespace(L)
		.beginNamespace("sdl")

		.beginClass <SDL::Color>("color")
		.addData("r", &SDL::Color::r)
		.addData("g", &SDL::Color::g)
		.addData("b", &SDL::Color::b)
		.addData("a", &SDL::Color::a)
		.endClass()

		.deriveClass<SDL::Color, SDL::Color>("rgba")
		.addConstructor <void(*) (int r, int g, int b, int a)>()
		.endClass()

		.deriveClass<SDL::Color, SDL::Color>("rgb")
		.addConstructor <void(*) (int r, int g, int b)>()
		.endClass()

		.beginClass<ResourceDatFile>("resourceDat")
		.addConstructor <void(*) (const std::string & filename)>()
		.addFunction("reload", &ResourceDatFile::reload)
		.endClass()

		.beginClass<Blob>("blob")
		.addData("length", &Blob::length, false)
		.endClass()

		.deriveClass<BlobFromFile, Blob>("blobFromFile")
		.addConstructor <void(*) (const std::string & filename)>()
		.endClass()

		.deriveClass<BlobFromResourceDat, Blob>("blobFromResourceDat")
		.addConstructor <void(*) (const ResourceDatFile *dat, const std::string & filename)>()
		.endClass()

		.beginClass <SDL::TextSettings>("textsettings")
		.addConstructor <void(*) ()>()
		.addData("antialias", &SDL::TextSettings::antialias)
		.addData("color", &SDL::TextSettings::color)
		.addData("outlineWidth", &SDL::TextSettings::outlineWidth)
		.addData("outlineColor", &SDL::TextSettings::outlineColor)
		.endClass()

		.beginClass <SDL::Font>("font")
		.addConstructor <void(*) (const std::string & name, double size)>()
		.endClass()

		.deriveClass <SDL::FileFont, SDL::Font>("filefont")
		.addConstructor <void(*) (const std::string & name, double size)>()
		.endClass()

		.deriveClass <SDL::FileFont, SDL::Font>("filefontFromBlob")
		.addConstructor <void(*) (const Blob *blob, double size)>()
		.endClass()

		.beginClass <SDL::Surface>("surface")
		.addConstructor <void(*) (const std::string & s)>()
		.addFunction("w", &SDL::Surface::w)
		.addFunction("h", &SDL::Surface::h)
		.addData("x", &SDL::Surface::x, false)
		.addData("y", &SDL::Surface::y, false)
		.addFunction("wasDrawn", &SDL::Surface::wasDrawn)
		.endClass()

		.deriveClass<SDL::Surface, SDL::Surface>("surfaceFromBlob")
		.addConstructor <void(*) (Blob *blob)>()
		.endClass()

		.deriveClass<SDL::Surface, SDL::Surface>("text")
		.addConstructor <void(*) (const SDL::Font *, const SDL::TextSettings *settings, const std::string & s)>()
		.endClass()

		.deriveClass<SDL::Surface, SDL::Surface>("outlined")
		.addConstructor <void(*) (SDL::Surface *base, int levels, SDL::Color *color)>()
		.endClass()

		.deriveClass<SDL::Surface, SDL::Surface>("scaled")
		.addConstructor <void(*) (int scaling, SDL::Surface *base)>()
		.endClass()

		
		.deriveClass<SurfaceColorMapped, SDL::Surface>("colormapped")
		.addConstructor <void(*) (SDL::Surface *parent, LuaRef r)>()
		.endClass()

		.deriveClass<SDL::SurfaceScreenshot, SDL::Surface>("screenshot")
		.addConstructor <void(*) ()>()
		.endClass()

		.beginClass <SDL::Screen>("screen")
		.addConstructor <void(*) ()>()
		.addFunction("w", &SDL::Screen::w)
		.addFunction("h", &SDL::Screen::h)
		.addFunction("begin", &SDL::Screen::begin)
		.addFunction("finish", &SDL::Screen::finish)
		.addFunction("blit", &SDL::Screen::blit)
		.addFunction("drawrect", &SDL::Screen::drawrect)
		.addFunction("clip", &SDL::Screen::clip)
		.addFunction("unclip", &SDL::Screen::unclip)
		.endClass()

		.beginClass <DrawHook>("drawHook")
		.addConstructor <void(*) (LuaRef r)>()
		.endClass()

		.beginClass <EventHook>("eventHook")
		.addConstructor <void(*) (LuaRef r)>()
		.endClass()

		.beginClass <SDL::Event>("event")
		.addConstructor <void(*) ()>()
		.addFunction("type", &SDL::Event::type)
		.addFunction("x", &SDL::Event::x)
		.addFunction("y", &SDL::Event::y)
		.addFunction("wheel", &SDL::Event::wheely)
		.addFunction("keycode", &SDL::Event::keycode)
		.addFunction("mousebutton", &SDL::Event::mousebutton)
		.endClass()

		.deriveClass <SDL::EventLoop, SDL::Event>("eventloop")
		.addConstructor <void(*) ()>()
		.addFunction("next", &SDL::EventLoop::next)
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
		.addFunction("reset", &SDL::Timer::reset)
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

		.endNamespace();

	getGlobalNamespace(L)
		.beginNamespace("os")

		.addFunction("log", OS::log)
		.addFunction("isshiftdown", OS::isshiftdown)
		.addFunction("mtime", OS::mtime)
		.addFunction("getKnownFolder", OS::getKnownFolder)
		.addFunction("mkdir", OS::mkdir)

		.addCFunction("messagebox", &messagebox)
		.addCFunction("listall", &listDirectory)
		.addCFunction("listfiles", &listDirectoryFiles)
		.addCFunction("listdirs", &listDirectoryDirs)

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
