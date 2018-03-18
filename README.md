# IntoTheBreachLua

This library works as a proxy for multiple DLLs for the [Into the Breach](https://subsetgames.com/itb.html) game in order to provide additional functionality to the modding community.

## Installation
If you downloaded a binary release (an archive with a buch of dlls and folders in it) the installation procedure is as follows:
1. Install [mod loader](https://subsetgames.com/forum/viewtopic.php?f=26&t=32833&sid=7dae5dbaf729740ce2019cd048c37e99).
2. Extract evertything from the archive into game directory, overwriting, among others, lua5.1.dll and SDL2.dll.

This is it. Apart from installing API for mods, this will also install squad selection dialog (making it easier to play squads added by other mods).

If you want to only install API and don't want squad selection (for whatever reasons), only extract .dll files from the archive.

## API
A number of functions are added to game's lua VMs. A full description of what's added is in [api.md](api.md) file.

## Error reporting
Lua errors that happen in game are dumped to error.txt file. If something doesn't work right in your script and the game is being secretive about what exactly, check errors.txt.

## Overloading lua5.1.dll functions
This section is for those who wish to overload the functionality of Lua library function that the game uses.

For example, error reporting and autoexec functionality is made possible by overloading.

The ```HOOK(name,rettype,args)``` macro from ```lua5.1.h``` allows you to write your own wrapper (or implementation) for exported lua functions.
Arguments are:
- ```name``` - The name of lua function, without quotes. It has to be one of about hundred functions explored by the dll, or you will get compilation errors.
- ```rettype``` - return type of the lua function.
- ```args``` - list of arguments inside parentheses.

Additionally, a static pointer to pointer to function is created when you use the macro, with name dll_<name> (it's named dll_lua_tolstring in example above), and it can be used to call the function from original dll like this:

```c
const char *myString = (*dll_lua_tolstring)(L, idx, len);
```

Here is example usage:
```c
HOOK(lua_tolstring, const char *, (lua_State *L, int idx, size_t *len)) {
	// put your implementation here
	log("lua_tolstring was called by the game!\n");

	// this is a call to lua_tolstring function from actual Lua dll.
	return (*dll_lua_tolstring)(L, idx, len);
}
```

By default, lua functions are exported using exports.def file with names like ```__E__102__```. Those functions are generated automatically and are implemented in ```lua5.1.cc```. When you use the ```HOOK``` macro to reimplement one of those functions, you have to remove corresponding line from ```exports.def```.

Some functions are already reimplemented in ```lua-hooks.cc```.

If you want to use any of lua functions in your code, you have to reimplement them using the HOOK macro, even if reimplementation does nothing but calls the original.
