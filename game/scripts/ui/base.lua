Ui = Class.new()

function Ui:new()
  	self.children = {}
	self.captiontext = ""
	self.w = 0
	self.h = 0
	self.x = 0
	self.y = 0
	self.dx = 0
	self.dy = 0
	self.padt = 0
	self.padr = 0
	self.padb = 0
	self.padl = 0
	self.screenx = 0
	self.screeny = 0
	self.font = uifont
	self.textset = uitextset
	self.innerHeight = 0
	self.bgcolor = nil
	self.rect = sdl.rect(0,0,0,0)
	self.decorations = {}
	self.pressed = false
	self.hovered = false
	self.disabled = false
	self.root = self

end

function Ui:add(child)
	child:setroot(self.root)
	table.insert(self.children,child)
	
	if self.nofitx == nil then
		if self.w > 0 and child.w + child.x > self.w - self.padl - self.padr then
			child.w = self.w - self.padl - self.padr - child.x
		end
	end
	
	if self.nofity == nil then
		if self.h > 0 and child.h + child.y > self.h - self.padt - self.padb then
			child.h = self.h - self.padt - self.padb - child.y
		end
	end
	
	return self
end

function Ui:setroot(root)
	self.root = root
	
	for i=1,#self.children do
		self.children[i]:setroot(root)
	end
end

function Ui:decorate(decorations)
	for i=1,#self.decorations do
		self.decorations[i]:unapply(self)
	end

	self.decorations = decorations
	
	for i=1,#self.decorations do
		self.decorations[i]:apply(self)
	end

	return self
end

function Ui:pos(x, y)
	self.x = -x
	self.y = -y
	
	return self
end

function Ui:pospx(x, y)
	self.x = x
	self.y = y
	
	return self
end

function Ui:caption(text)
	self.captiontext = text
	
	return self
end

function Ui:padding(v)
	self.padt = self.padt + v
	self.padr = self.padr + v
	self.padb = self.padb + v
	self.padl = self.padl + v

	return self
end

function Ui:width(w)
	self.w = -w
	return self
end

function Ui:height(h)
	self.h = -h
	return self
end

function Ui:widthpx(w)
	self.w = w
	return self
end

function Ui:heightpx(h)
	self.h = h
	return self
end

function Ui:wheel(mx,my,y)
	for i=1,#self.children do
		local child = self.children[i]
		
		if mx>=child.screenx and mx<child.screenx+child.w and my>=child.screeny and my<child.screeny+child.h then
			if child:wheel(mx,my,y) then
				return true
			end
		end
	end

	return false
end

function Ui:mousedown(mx, my)
	if self.root.pressedchild ~= nil then
		self.root.pressedchild.pressed = false
	end
	
	self.root.pressedchild = self
	self.pressed = true

	for i=1,#self.children do
		local child = self.children[i]
		local match = mx>=child.screenx and mx<child.screenx+child.w and my>=child.screeny and my<child.screeny+child.h
		
		if match then
			if child:mousedown(mx, my) then
				return true
			end
		end
	end

	return false
end

function Ui:mouseup(mx, my)
	if self.root.pressedchild == self and not self.disabled then
		self:clicked()
		return true
	end

	for i=1,#self.children do
		local child = self.children[i]
		
		if mx>=child.screenx and mx<child.screenx+child.w and my>=child.screeny and my<child.screeny+child.h then
			if child:mouseup(mx, my) then
				return true
			end
		end
	end

	return false
end

function Ui:mousemove(mx, my)
	if self.root.hoveredchild ~= nil then
		self.root.hoveredchild.hovered = false
	end
	
	self.root.hoveredchild = self
	self.hovered = true

	for i=1,#self.children do
		local child = self.children[i]
		
		if
			mx>=child.screenx and
			mx<child.screenx+child.w and
			my>=child.screeny and
			my<child.screeny+child.h
		then
			self.root.hoveredchild = child
			if child:mousemove(mx, my) then
				return true
			end
		end
	end

	return false
end

function Ui:relayout()
	local innerHeight = 0

	for i=1,#self.children do
		local child = self.children[i]
		
		if child.w < 0 then child.w = (self.w - self.padl - self.padr) * -child.w end
		if child.h < 0 then child.h = (self.h - self.padt - self.padb) * -child.h end
		if child.x < 0 then child.x = (self.w - self.padl - self.padr) * -child.x end
		if child.y < 0 then child.y = (self.h - self.padt - self.padb) * -child.y end
		
		child.screenx = self.screenx + self.padl - self.dx + child.x
		child.screeny = self.screeny + self.padt - self.dy + child.y
		
		child:relayout()
		
		local childbottom = self.padt + child.y + child.h + self.padb
		if innerHeight < childbottom then innerHeight = childbottom end
		
		child.rect.x = child.screenx
		child.rect.y = child.screeny
		child.rect.w = child.w
		child.rect.h = child.h
	end
	
	self.innerHeight = innerHeight
end

function Ui:draw(screen)
	self.decorationx = 0
	self.decorationy = 0
	for i=1,#self.decorations do
		local decoration = self.decorations[i]
		decoration:draw(screen, self)
	end

	for i=1,#self.children do
		local child = self.children[i]
		child:draw(screen)
	end
end

function Ui:clicked()
	if self.onclicked ~= nil then
		self:onclicked()
	end
end


