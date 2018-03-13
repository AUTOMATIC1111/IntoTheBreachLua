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

#### sdl.screen
A help class that lets you draw on game's screen.
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

screen:update() -- call after drawing a bunch of things to have them appear on game screen
```

not finished