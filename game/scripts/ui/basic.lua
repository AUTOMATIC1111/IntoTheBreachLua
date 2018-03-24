UiCheckbox = Class.inherit(Ui)

function UiCheckbox:new()
	Ui.new(self)
	self.checked = false
end

function UiCheckbox:clicked()
	self.checked = not self.checked
	
	Ui.clicked(self)
end


UiScrollArea = Class.inherit(Ui)

function UiScrollArea:new()
	Ui.new(self)

	self.scrollcolor = sdl.rgb(64,64,64)
	self.scrollrect = sdl.rect(0,0,0,0)

	self.scrollbuttoncolor = sdl.rgb(128,128,128)
	self.scrollbuttonrect = sdl.rect(0,0,0,0)

	self.scrollwidth = 16
	self.buttonheight = 0
	
	self.padr = self.padr + self.scrollwidth
	
	self.nofity = true
end

function UiScrollArea:draw(screen)
	screen:clip(sdl.rect(self.screenx,self.screeny,self.w,self.h))
	Ui.draw(self, screen)
	
	if self.innerHeight > self.h then
		screen:drawrect(self.scrollcolor,self.scrollrect)
		screen:drawrect(self.scrollbuttoncolor,self.scrollbuttonrect)
	end
	
	screen:unclip()
end

function UiScrollArea:relayout()
	Ui.relayout(self)
	
	self.scrollrect.x = self.screenx + self.w - self.scrollwidth
	self.scrollrect.y = self.screeny
	self.scrollrect.w = self.scrollwidth
	self.scrollrect.h = self.h
	
	local ratio = self.h / self.innerHeight
	local offset = self.dy / (self.innerHeight - self.h)
	if ratio > 1 then ratio = 1 end
	
	self.buttonheight = ratio * self.h
	self.scrollbuttonrect.x = self.screenx + self.w - self.scrollwidth
	self.scrollbuttonrect.y = self.screeny + offset * (self.h - self.buttonheight)
	self.scrollbuttonrect.w = self.scrollwidth
	self.scrollbuttonrect.h = self.buttonheight
end

function UiScrollArea:mousedown(x, y)
	if x < self.scrollrect.x then return Ui.mousedown(self, x, y) end

	local ratio = (y - self.screeny - self.buttonheight/2) / (self.h-self.buttonheight)
	if ratio < 0 then ratio = 0 end
	if ratio > 1 then ratio = 1 end
	
	self.dy = ratio * (self.innerHeight - self.h)
	
	return true
end

function UiScrollArea:wheel(mx,my,y)
	self:relayout()

	self.dy = self.dy - y * 20
	if self.dy < 0 then self.dy = 0 end
	if self.dy + self.h > self.innerHeight then self.dy = self.innerHeight - self.h end
	if self.h > self.innerHeight then self.dy=0 end

	return true
end
