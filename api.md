#### sdl.color
Represents a color to be used with other functions.

```
local color = sdl.rgba(r,g,b,a) -- all values are 0-255
local color = sdl.rgb(r,g,b) -- all values are 0-255
```

#### sdl.resourceDat
A reader for .dat files (game stores a lot of its assets in resources/resource.dat).
```
local resourceDat = sdl.resourceDat("resources/resource.dat")
resourceDat:reload() -- this causes file index to be reloaded, and has to be called every time you edit the .dat file
```

#### sdl.blob
Respresents a blob of data stored in memory.
```
local blob = sdl.blobFromFile("test.png") -- reads file test.png in game directory
local blobFont = sdl.blobFromResourceDat(resourceDat,"fonts/Justin13.ttf") -- reads file fonts/Justin13.ttf from resource.dat archive
```

#### sdl.textsettings
Represents settings for text drawing.
```
local textset = sdl.textsettings()
textset.antialias = false -- whether text should be antialiased when rendering
textset.color = sdl.rgb(255,255,255) -- text color
```

#### sdl.font
Represents font for text drawing.
```
local font = sdl.font("Courier",18) -- arguments are font family name and size
local smallfont = sdl.filefont("resources/mods/JustinFont8.ttf",12)
local largefont = sdl.filefontFromBlob(sdl.blobFromResourceDat(resourceDat,"fonts/Justin15.ttf"),18)
```

#### sdl.surface
An image in memory.
```
local surf = sdl.surface("icon.png")
local w = surf:w() -- width
local h = surf:h() -- height

-- create a new surface by reading an image file from resource.dat
local surface = sdl.surfaceFromBlob(sdl.blobFromResourceDat(resourceDat,"img/units/player/mech_punch_ns.png"))

-- create a new surface as an existing one with an outline with specified width and color
local outl = sdl.outlined(surf,1,sdl.color(255,0,0))

-- create a new surface as an existing one, but scaled
local scaled = sdl.scaled(2, surf)

-- create a new surface by rendering text
local textsurf = sdl.text(font,textset,"hello!")

-- createw a new surface by taking a screenshot of the game window
local screenshot = sdl.screenshot()

if surf:wasDrawn() then
    -- wasDrawn() returns true if the image in surface was used by the game to draw
    -- previous frame. This can be useful to find out game state.
end
```

#### sdl.rect
A rectangle.
```
local rect = sdl.rect(0,0,100,100) -- (left,top,width,height)
rect.x = 20
rect.y = 40
rect.w = 200
rect.h = 400
```

#### sdl.event
An event. The ```event:type()``` function returns a value that can be compared to any of the following:
```
sdl.events.quit -- user closed the game window
sdl.events.keydown -- user pressed a button; call event:keycode() to figure out which
sdl.events.keyup -- user released a button
sdl.events.mousebuttondown -- user pressed a mouse button; call event:mousebutton() to know which one
sdl.events.mousebuttonup -- user released a mouse button
sdl.events.mousewheel -- user rotated a mouse wheel; call event:wheel() to get direction
```

Use [SDL Keycode Lookup Table](https://wiki.libsdl.org/SDLKeycodeLookup) with ```event:keycode()``` to figure out which key was pressed/released.

Mouse button codes are:

| Mouse button  | ```event:mousebutton()``` |
|---------------|---|
| Left          | 1 |
| Middle        | 2 |
| Right         | 3 |
| X1            | 4 |
| X2            | 5 |

#### sdl.eventloop
An event loop helper class that can be used to set up own SDL event loop, independent from game's loop.
```
local eventloop = sdl.eventloop();
while eventloop:next() do
	local type = eventloop:type();
    
	<...>
end
```
Has all functions from ```sdl.event``` in addition to ```eventloop:next()```.

#### sdl.eventHook
```
My_Custom_Event_Hook = sdl.eventHook(function(event)
	if event:type() == sdl.events.mousebuttondown then
		if sdl.mouse.x() < 20 and sdl.mouse.y() < 20 then
			-- this code is executed when user clicks the top left corner of the screen with his mouse
			messagebox("Well done!")
			return true
		end
		return false
	end
end)
```
Registers a function to be called whenever an event happens in-game. This function is called with a single argument - an sdl.event object. The function you're registering must return true if you handled the event and don't want the game (or other mods) to know about it. If you return false, the event will be passed to other mods, and then possibly to game.
As soon as the object returned by `sdl.eventHook()` is deleted by lua, the hook is removed, so you must store the result of `sdl.eventHook()` call into some global variable.

#### sdl.screen
A helper class that lets you draw on game's screen.
```
local screen = sdl.screen()
local w = screen:w() -- width
local h = screen:h() -- height

screen:start() -- all drawing must happen between calls to start() and finish()

screen:blit(surf,rect,x,y) -- draws surface on the screen
                           -- arguments are:
                           --   surface: surface to draw
                           --   rectangle: rectangle inside that surface that will be drawn
                           --              if nil, whole surface is drawn
                           --   x, y: position on screen where to draw

screen:drawrect(rect, sdl:rgb(128,128,128)) -- draw a rectangle

screen:clip(rect) -- prevents pixels outside the rectangle to be changed
screen:unclip() -- undoes the effect of previous function

screen:finish() -- call after drawing a bunch of things to have them appear on game screen
```
The intended approach is to create an sdl.scren object, then do a loop using sdl.eventloop, effectively pausing the game as long as screen object exists. This class does not allow you to draw seamlessly with running game.

An example of such loop is:
```
local screen = sdl.screen()
local eventloop = sdl.eventloop()
local quit = 0
local pointer = sdl.surface("resources/mods/ui/pointer.png");
local mouserect = sdl.rect(sdl.mouse.x(), sdl.mouse.y(), pointer:w(), 	local screenshot = sdl.screenshot()
pointer:h())

while quit == 0 do
	while eventloop:next() do
		local type = eventloop:type();
		
		if type == sdl.events.quit then
			quit = 1
		elseif type == sdl.events.keydown and eventloop:keycode() == 27 then
			quit = 1
		elseif type == sdl.events.mousemotion then
			mouserect.x = eventloop:x();
			mouserect.y = eventloop:y();
		end
	end

    screen:start()
	screen:blit(screenshot, nil, 0, 0)
	screen:blit(pointer, nil, mouserect.x, mouserect.y)
	screen:finish()
end
```

#### sdl.drawHook
```
function frameHook(screen)
	screen:blit(itworks,nil,64,430)
end
drawHookPilots = sdl.drawHook(frameHook)
```
Registers a function to be called just before a frame is drawn. This function is called with a single argument - an sdl.screen object. You must use that object to draw over what the game drew. screen:begin() and screen:finish() are already called by the library, so don't call them in the hook function.
As soon as the object is deleted by lua, the hook is removed, so you must store the result of sdl.drawHook() call into some global variable.

Here is an example of code that would draw itworks.png picture whenever a repair skill icon is displayed on screen: ("repair.png" is the repair icon from "img/weapons/repair.png" from resource.dat).

```
local itworks=sdl.surface(self.resourcePath.."itworks.png")
local repairIcon=sdl.surface(self.resourcePath.."repair.png")
function frameHook(screen)
	if repairIcon:wasDrawn() then
		screen:blit(itworks,nil,64,430)
	end
end

drawHookPilots = sdl.drawHook(frameHook)
```

#### sdl.timer
A timer object that lets you measure the amount of time passed in milliseconds since timer's creation.
```
local timer = sdl.timer()
<do some work here>
local timeTaken = timer:elapsed()
```

#### sdl.mouse
A namespace with function for getting mouse coordinates.
```
local x = sdl.mouse.x() -- note that sdl.mouse is not an object, and you have to use .x(), not :x()
local y = sdl.mouse.y()
```

#### sdl.log(text)
A function that prints text to log.txt file.
```
sdl.log("Testing!")
```

#### sdl.isshiftdown()
A function that tells you if shift is pressed
```
if(sdl.isshiftdown()) then
	sdl.log("it is")
end
```

#### messagebox(text)
Shows default windows message box with text in it.

#### listall(dirname)
Non-recursively lists all entries inside directory dirname.

#### listfiles(dirname)
Non-recursively lists all files inside directory dirname.
```
local modlist = listdirs("mods")
for key,value in pairs(modlist) do
	table.insert(self.mod_dirs,value)
end
```
#### listdirs(dirname)
Non-recursively lists all directories inside directory dirname.
