# IntoTheBreachLua

This library works as a proxy for lua5.1.dll for the [Into the Breach] game.
You rename lua5.1.dll in game directory to lua5.1-original.dll, and put this library in place of it.
The game loads this library, which loads lua5.1-original.dll, passing calls to any of exported functions to it.

## Overloading lua5.1.dll functions
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

## Implemented lua functions
This library creates those lua functions for every lua VM in the game:
 - ```messagebox(text)``` - shows default windows message box with text in it.
 - ```listall(dirname)``` - lists all entries inside directory dirname.
 - ```listfiles(dirname)``` - lists all files inside directory dirname.
 - ```listdirs(dirname)``` - lists all directories inside directory dirname.


   [Into the Breach]: <https://subsetgames.com/itb.html>
