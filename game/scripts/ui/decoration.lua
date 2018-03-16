local white = sdl.rgb(255,255,255)
local black = sdl.rgb(0,0,0)
local buttoncolor = sdl.rgb(24,28,40)
local buttonbordercolor = sdl.rgb(73,92,121)
local buttonhlcolor = sdl.rgb(217,235,200)
local buttondisabledcolor = sdl.rgb(80,80,80)

local function textset(color,outlineColor,outlineWidth)
	local res = sdl.textsettings()
	
	res.antialias = false
	res.color = color
	res.outlineColor = outlineColor or white
	res.outlineWidth = outlineWidth or 0

	return res
end

local justin13 = sdl.filefont("resources/mods/Justin13.ttf",13)
local justin15 = sdl.filefont("resources/mods/Justin15.ttf",18)

local uifont = {
	default = {
		font = justin13,
		set = textset(white),
	},
	title = {
		font = justin15,
		set = textset(white,sdl.rgb(35,42,59),2),
	},
}

UiDeco = Class.new()
function UiDeco:new()

end

function UiDeco:draw(screen,widget)
end

function UiDeco:apply(widget)
end

function UiDeco:unapply(widget)
end

DecoSolid = Class.inherit(UiDeco)
function DecoSolid:new(color)
	self.color = color
end

function DecoSolid:draw(screen,widget)
	if self.color ~= nil and widget.rect ~= nil then
		screen:drawrect(self.color, widget.rect)
	end
end

DecoFrame = Class.inherit(UiDeco)
function DecoFrame:new(color,bordercolor)
	self.color = color or buttoncolor
	self.bordercolor = bordercolor or buttonbordercolor
	self.rect = sdl.rect(0,0,0,0)
end

function DecoFrame:draw(screen,widget)
	local r = widget.rect

	screen:drawrect(self.color, r)
	
	self.rect.x=r.x
	self.rect.y=r.y
	self.rect.w=2
	self.rect.h=r.h
	screen:drawrect(self.bordercolor, self.rect)
	self.rect.x=r.x+r.w-2
	screen:drawrect(self.bordercolor, self.rect)
	
	self.rect.x=r.x
	self.rect.y=r.y
	self.rect.w=r.w
	self.rect.h=2
	screen:drawrect(self.bordercolor, self.rect)
	self.rect.y=r.y+r.h-2
	screen:drawrect(self.bordercolor, self.rect)
end

function DecoFrame:apply(widget)
	widget:padding(2)
end

function DecoFrame:unapply(widget)
	widget:padding(-2)
end


DecoButton = Class.inherit(UiDeco)
function DecoButton:new(color,bordercolor,hlcolor)
	self.color = color or buttoncolor
	self.bordercolor = bordercolor or buttonbordercolor
	self.hlcolor = hlcolor or buttonhlcolor
	self.disabledcolor = buttondisabledcolor
	
	self.rect = sdl.rect(0,0,0,0)
end

function DecoButton:draw(screen,widget)
	local r = widget.rect

	screen:drawrect(self.color, r)
	
	local color = self.bordercolor
	if widget.hovered then
		color = self.hlcolor
	end
	if widget.disabled then
		color = self.disabledcolor
	end
	
	self.rect.x=r.x
	self.rect.y=r.y
	self.rect.w=1
	self.rect.h=r.h
	screen:drawrect(color, self.rect)
	self.rect.x=r.x+r.w-1
	screen:drawrect(color, self.rect)
	
	self.rect.x=r.x
	self.rect.y=r.y
	self.rect.w=r.w
	self.rect.h=1
	screen:drawrect(color, self.rect)
	self.rect.y=r.y+r.h-1
	screen:drawrect(color, self.rect)

	self.rect.x=r.x+2
	self.rect.y=r.y+2
	self.rect.w=2
	self.rect.h=r.h-4
	screen:drawrect(color, self.rect)
	self.rect.x=r.x+r.w-4
	screen:drawrect(color, self.rect)
	
	self.rect.x=r.x+2
	self.rect.y=r.y+2
	self.rect.w=r.w-4
	self.rect.h=2
	screen:drawrect(color, self.rect)
	self.rect.y=r.y+r.h-4
	screen:drawrect(color, self.rect)
	
	widget.decorationx = widget.decorationx + 8
end

function DecoButton:apply(widget)
	widget:padding(5)
end

function DecoButton:unapply(widget)
	widget:padding(-5)
end

DecoSurface = Class.inherit(UiDeco)
function DecoSurface:new(surface)
	self.surface = surface
end

function DecoSurface:draw(screen,widget)
	if self.surface == nil then return end
	local r = widget.rect

	screen:blit(self.surface, nil, r.x + widget.decorationx, r.y + widget.decorationy + r.h/2 - self.surface:h()/2)
	
	widget.decorationx = widget.decorationx + self.surface:w()
end

DecoSurfaceOutlined = Class.inherit(DecoSurface)
function DecoSurfaceOutlined:new(surface,levels,bordercolor,hlcolor)
	self.surfacenormal = sdl.scaled(2,sdl.outlined(surface,levels or 1,bordercolor or buttonbordercolor))
	self.surfacehl = sdl.scaled(2,sdl.outlined(surface,levels or 1,hlcolor or buttonhlcolor))
end

function DecoSurfaceOutlined:draw(screen,widget)
	if widget.hovered then self.surface = self.surfacehl else self.surface = self.surfacenormal end

	DecoSurface.draw(self,screen,widget)
end

DecoText = Class.inherit(DecoSurface)
function DecoText:new(text, font, textset)
	self.font = font or uifont.default.font
	self.textset = textset or uifont.default.set
	self.text = text or ""

	DecoSurface.new(self, sdl.text(self.font,self.textset,self.text))
end

function DecoText:setsurface(text)
	if text ~= self.text then
		self.text = text
		self.surface = sdl.text(self.font,self.textset,self.text)
	end
end

DecoCaption = Class.inherit(DecoText)
function DecoCaption:new(font, textset)
	DecoText.new(self, self.text, font, textset)
end

function DecoCaption:draw(screen,widget)
	self:setsurface(widget.captiontext)
	
	DecoText.draw(self,screen,widget)
end

DecoFrameCaption = Class.inherit(DecoCaption)
function DecoFrameCaption:new(color, font, textset)
	self.color = color or buttonbordercolor
	self.height = 40
	self.rect = sdl.rect(0,0,0,0)
	
	DecoCaption.new(self, uifont.title.font, uifont.title.set)
end

function DecoFrameCaption:draw(screen,widget)
	self:setsurface(widget.captiontext)

	local r = widget.rect
	
	self.rect.x = r.x
	self.rect.y = r.y
	self.rect.w = r.w
	self.rect.h = self.height
	
	screen:drawrect(self.color, self.rect)
	local offset = self.height/2 - self.surface:h()/2 + 2
	screen:blit(self.surface, nil, r.x + offset, r.y + offset)
end

function DecoFrameCaption:apply(widget)
	widget.padt = self.height
end

function DecoFrameCaption:unapply(widget)
	widget.padt = 0 --oops
end

local checkboxChecked = sdl.surface("resources/mods/ui/checkbox-checked.png")
local checkboxUnchecked = sdl.surface("resources/mods/ui/checkbox-unchecked.png")
local checkboxHoveredChecked = sdl.surface("resources/mods/ui/checkbox-hovered-checked.png")
local checkboxHoveredUnchecked = sdl.surface("resources/mods/ui/checkbox-hovered-unchecked.png")

DecoCheckbox = Class.inherit(DecoSurface)
function DecoCheckbox:new()
	DecoSurface.new(self, checkboxUnchecked)
end

function DecoCheckbox:draw(screen,widget)
	if widget.checked ~= nil and widget.checked then
		if widget.hovered then
			self.surface = checkboxHoveredChecked
		else
			self.surface = checkboxChecked
		end
	else
		if widget.hovered then
			self.surface = checkboxHoveredUnchecked
		else
			self.surface = checkboxUnchecked
		end
	end
	
	DecoSurface.draw(self, screen, widget)
end
