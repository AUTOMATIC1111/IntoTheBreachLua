UiRoot = Class.inherit(Ui)

function UiRoot:new()
	Ui.new(self)
	
	self.hoveredchild = nil
	self.pressedchild = nil
end

function UiRoot:draw(screen)
	self:relayout()

	Ui.draw(self, screen)
end

function UiRoot:event(eventloop)
	local type = eventloop:type();
	local mx = sdl.mouse.x();
	local my = sdl.mouse.y();
	
	if type == sdl.events.mousewheel then
		return self:wheel(mx,my,eventloop:wheel())
	end

	if type == sdl.events.mousebuttondown then
		return self:mousedown(mx, my)
	end
	
	if type == sdl.events.mousebuttonup then
		local res = self:mouseup(mx, my)
		self.pressedchild = nil
		return res
	end
	
	if type == sdl.events.mousemotion then
		if self.hoveredchild ~= nil then
			self.hoveredchild.hovered = false
		end
		self.hoveredchild = nil
		
		return self:mousemove(mx, my)
	end
end
