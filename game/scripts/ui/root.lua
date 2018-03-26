UiRoot = Class.inherit(Ui)

function UiRoot:new()
	Ui.new(self)
	
	self.hoveredchild = nil
	self.pressedchild = nil
	self.translucent = true
end

function UiRoot:draw(screen)
	self:relayout()

	Ui.draw(self, screen)
end

function UiRoot:event(eventloop)
	if not self.visible then return false end
	
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
		local child = self.pressedchild
		if child ~= nil and mx>=child.screenx and mx<child.screenx+child.w and my>=child.screeny and my<child.screeny+child.h then
			if child:mouseup(mx, my) then
				self.pressedchild = nil
				child.pressed = false
				return true
			end
		end
		
		local res = self:mouseup(mx, my)
		self.pressedchild = nil
		return res
	end
	
	if type == sdl.events.mousemotion then
		if self.hoveredchild ~= nil then
			self.hoveredchild.hovered = false
		end
		self.hoveredchild = nil

		if self.pressedchild ~= nil then
			if self.pressedchild:mousemove(mx, my) then
				return false
			end
		end
		
		-- XXX
		self:mousemove(mx, my)
		return false
	end
end
