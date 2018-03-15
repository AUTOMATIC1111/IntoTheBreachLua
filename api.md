#### sdl.color
Represents a color to be used with other functions.

```
local color = sdl.rgba(r,g,b,a) -- all values are 0-255
local color = sdl.rgb(r,g,b) -- all values are 0-255
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
local smallfont = sdl.filefont("resources/mods/JustinFont8.ttf",12);
```

#### sdl.surface
An image in memory.
```
local surf = sdl.surface("icon.png")
local w = surf:w() -- width
local h = surf:h() -- height

-- create a new surface as an existing one with an outline with specified width and color
local outl = sdl.outlined(surf,1,sdl.color(255,0,0))

-- create a new surface by rendering text
local textsurf = sdl.text(font,textset,"hello!")

-- createw a new surface by taking a screenshot of the game window
local screenshot = sdl.screenshot()

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

#### sdl.eventloop
An even loop helper class that can be used to set up own SDL event loop, independent from game's loop.
```
local eventloop = sdl.eventloop();
while eventloop:next() do
	local type = eventloop:type();
    
	<...>
end
```
The ```eventloop:type()``` function returns a value that can be compared to any of the following:
```
sdl.events.quit -- user closed the game window
sdl.events.keydown -- user pressed a button; call eventloop:keycode() to figure out which
sdl.events.keyup -- user released a button
sdl.events.mousebuttondown -- user pressed a mouse button; call eventloop:mousebutton() to know which one
sdl.events.mousebuttonup -- user released a mouse button
sdl.events.mousewheel -- user rotated a mouse wheel; call eventloop:wheel() to get direction
```

Use [SDL Keycode Lookup Table](https://wiki.libsdl.org/SDLKeycodeLookup) with ```eventloop:keycode()``` to figure out which key was pressed/released.

Mouse button codes are:

| Mouse button  | ```eventloop:mousebutton()``` |
|---------------|---|
| Left          | 1 |
| Middle        | 2 |
| Right         | 3 |
| X1            | 4 |
| X2            | 5 |

#### sdl.screen
A helper class that lets you draw on game's screen.
```
local screen = sdl.screen()
local w = screen:w() -- width
local h = screen:h() -- height

screen:blit(surf,rect,x,y) -- draws surface on the screen
                           -- arguments are:
                           --   surface: surface to draw
                           --   rectangle: rectangle inside that surface that will be drawn
                           --              if nil, whole surface is drawn
                           --   x, y: position on screen where to draw

screen:drawrect(rect, sdl:rgb(128,128,128)) -- draw a rectangle

screen:clip(rect) -- prevents pixels outside the rectangle to be changed
screen:unclip() -- undoes the effect of previous function

screen:start() -- all drawing must happen between calls to start() and finish()
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
