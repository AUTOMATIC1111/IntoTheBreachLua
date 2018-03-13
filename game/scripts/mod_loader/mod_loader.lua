--lfs = require("lfs")
mod_loader = {}

function mod_loader:init()
	self.mod_dirs = {}
	self.mods = {}
	self.mod_options = {}
	
	self:enumerateMods()
	
	local savedOrder = {}--In case we ever get the ability to arrange the load order ourselves like with the Slipstream mod manager for FTL this would be taken from the savefile
	
	local orderedMods = self:orderMods(self:getModContentDefaults(),savedOrder)
	for i, id in ipairs(orderedMods) do
		modApi:setCurrentMod(id)
		self:initMod(id)
	end
	
	modApi:finalize()
	
	--Ideally we want to load only after opening a save so that we can handle mod configurations but without a way to modify the UI that's probably impossible :(
	self:loadModContent(self:getModContentDefaults(),savedOrder)
end

function mod_loader:enumerateMods()

	local modlist = listdirs("mods")
	for key,value in pairs(modlist) do
		table.insert(self.mod_dirs,value)
	end

	for i, dir in pairs(self.mod_dirs) do
		local err = ""
		local path = string.format("mods/%s/scripts/init.lua",dir)
		local function fn()
			return dofile(path)
		end
		
		local ok, data = xpcall(fn,function(e) err = e end)
		
		if ok and type(data) ~= "table" then
			ok = false
			err = "Missing data"
		end
		
		if ok and type(data.id) ~= "string" then
			ok = false
			err = "Missing id"
		end
		
		if ok and self.mods[data.id] then
			ok = false
			err = string.format("Duplicate mod with id [%s] found at [%s]",data.id,self.mods[data.id].dir)
		end
		
		if ok and type(data.init) ~= "function" then
			ok = false
			err = "Missing init function"
		end
		
		if ok and type(data.load) ~= "function" then
			ok = false
			err = "Missing load function"
		end
		
		if ok and type(data.name) ~= "string" then
			ok = false
			err = "Missing name"
		end
		
		--Proper version control could be handy, but there's no standardized format atm so whatever, each mod can use what they want
		
		--[[if ok and type(data.version) ~= "string" then
			ok = false
			err = "Missing version"
		end
		
		if ok and not version.parseVersion(data.version) then
			ok = false
			err = "Invalid version format"
		end]]
		
		if ok then
			data.dir = dir
			data.path = path
			data.scriptPath = string.format("mods/%s/scripts/",dir)
			data.resourcePath = string.format("mods/%s/",dir)--In case we somehow become able to load assets without repacking the game's rescource files
			
			data.installed = true
			
			self.mods[data.id] = data
			
			self.mod_options[data.id] = {
				options = {},--Potential for configurable mods?
				enabled = true,
				version = data.version,
			}
		end
		
		if not ok then
			LOG(string.format("Unable to mount mod at [%s]: %s",dir,err))
		end
	end
end

function mod_loader:initMod(id)
	local mod = self.mods[id]
	
	local function pinit()
		mod.init(mod)
	end
	local ok, err = xpcall(pinit,function(e) return string.format("Initializing mod [%s] with id [%s] failed: %s, %s",mod.name,id,e,debug.traceback()) end)
	if ok then
		LOG(string.format("Initialized mod [%s] with id [%s] successfully!",mod.name,id))
	else
		mod.installed = false
		LOG(err)
	end
end

function mod_loader:hasMod(id)
	return self.mods[id] and self.mods[id].installed
end

function mod_loader:getModContentDefaults()
	return copy_table(self.mod_options)
end

--This allows a mod to specify requirements = {"mod_id"} which will force the mod with the id "mod_id" to load before your mod
--Partially based off Lemonymous/Lemonhead's Sequential Mod Loader library for Invisible, Inc.
local function requireMod(self,options,ordered,traversed,id)
	if not traversed[id] and self:hasMod(id) and options[id] and options[id].enabled then
		traversed[id] = true
		
		if type(self.mods[id].requirements) == "table" then
			for i, requiredmod in ipairs(self.mods[id].requirements) do
				requireMod(self,options,ordered,traversed,requiredmod)
			end
		end
		
		options[id] = nil
		table.insert(ordered,id)
	end
end

function mod_loader:orderMods(options,savedOrder)
	local options = shallow_copy(options)
	
	
	local traversed = {}
	local ordered = {}
	
	--If we have saved an order since before we want that to have priority
	for i, id in ipairs(savedOrder) do
		requireMod(self,options,ordered,traversed,id)
	end
	
	--Sort the remaining options by id for consistency
	local sorted = {}
	for id in pairs(options) do
		local skip = false
		
		for i = 1, #sorted do
			if id < sorted[i] then
				table.insert(sorted,i,id)
				skip = true
				break
			end
		end
		
		if not skip then
			table.insert(sorted,id)
		end
	end
	
	for i, id in ipairs(sorted) do
		requireMod(self,options,ordered,traversed,id)
	end
	
	return ordered
end

function mod_loader:loadModContent(mod_options,savedOrder)
	LOG("--------LOADING MODS--------")
	
	--For helping with the standardized mod API--
	modApi:resetModContent()
	
	local orderedMods = self:orderMods(mod_options,savedOrder)
	
	for i, id in ipairs(orderedMods) do
		local mod = self.mods[id]
		modApi:setCurrentMod(id)
		
		local function pload()
			mod.load(mod,mod_options[id].options,mod_options[id].version)
		end
		local ok, err = xpcall(pload,function(e) return string.format("Loading mod [%s] with id [%s] failed: %s, %s",mod.name,id,e,debug.traceback()) end)
		if ok then
			LOG(string.format("Loaded mod [%s] with id [%s] successfully!",mod.name,id))
		else
			mod.installed = false
			LOG(err)
		end
	end
end

function modApi:selectSquads()
	local maxselected = 8

	local screen = sdl.screen()
	local eventloop = sdl.eventloop()
	local w = screen:w()
	local h = screen:h()
	local quit = 0

	local ui = UiRoot():widthpx(w):heightpx(h)
	
	-- bottom frame
	local framebot = Ui():width(0.6):heightpx(160):pos(0.2,0.7):padding(4):decorate({DecoFrame()})
	ui:add(framebot)

	framebot:add(Ui():width(1):height(0.2):pos(0,0):caption("You can have up to 8 squads selected at the same time."):decorate({DecoCaption()}))
	framebot:add(Ui():width(1):height(0.2):pos(0,0.2):caption("Hold SHIFT to open this dialog again."):decorate({DecoCaption()}))
	
	local labelcount = Ui():width(1):height(0.2):pos(0,0.4):caption(""):decorate({DecoCaption()})
	framebot:add(labelcount)
	
	local buttongo = Ui():pos(0,0.6):width(1):height(0.4):caption("Continue"):decorate({DecoButton(),DecoCaption()})
	framebot:add(buttongo)
	buttongo.onclicked = function()
		quit = 1
	end
	
	-- top frame
	local frametop = Ui():width(0.6):height(0.575):pos(0.2,0.1):caption("Choose squads"):decorate({DecoFrame(), DecoFrameCaption()})
	ui:add(frametop)

	local scrollarea = UiScrollArea():width(1):height(1):padding(12):decorate({DecoSolid(sdl.rgb(24,28,40))})
	frametop:add(scrollarea)

	local checkboxes = {}
	local updatecount = function()
		local count = 0
		
		for i=1,#checkboxes do
			local checkbox = checkboxes[i]
			if checkbox.checked then count=count+1 end
		end
		
		labelcount:caption("Selected "..count.." out of "..maxselected);
		buttongo.disabled = count > maxselected;
	end
	
	local pos=0
	for i=1,#modApi.squad_icon do
		local checkbox = UiCheckbox():pospx(0, pos):heightpx(41):width(1):decorate(
			{ DecoButton(), DecoCheckbox(), DecoSurfaceOutlined(sdl.surface(self.squad_icon[i])), DecoText(self.squad_text[(i-1)*2+1]) }
		)
		
		scrollarea:add( checkbox )
		pos = pos + 46
		
		checkbox.onclicked = function()
			updatecount()
		end
		
		table.insert(checkboxes, checkbox)
	end
	
	for i=1,maxselected do
		if self.squadIndices == nil then
			checkboxes[i].checked = true
		else
			checkboxes[self.squadIndices[i]].checked = true
		end
	end
	updatecount()
	
	local pointer = sdl.surface("resources/mods/ui/pointer.png");
	local mouserect = sdl.rect(sdl.mouse.x(), sdl.mouse.y(), pointer:w(), pointer:h())
	
	while quit == 0 do
		while eventloop:next() do
			local type = eventloop:type();
			
			ui:event(eventloop)
			
			if type == sdl.events.quit then
				quit = 1
			elseif type == sdl.events.keydown and eventloop:keycode() == 27 then
				quit = 1
			elseif type == sdl.events.mousemotion then
				mouserect.x = eventloop:x();
				mouserect.y = eventloop:y();
			end
		end
		
		ui:draw(screen)
		
		screen:blit(pointer, nil, mouserect.x, mouserect.y)
		screen:update()
	end
	
	self.squadIndices = {}
	local assignIndex = function(n)
		for i=1,maxselected do
			if self.squadIndices[i] == nil then
				self.squadIndices[i] = n
				return true
			end
		end
		return false
	end

	for i=1,maxselected do
		if checkboxes[i].checked then
			self.squadIndices[i] = i
		end
	end
	
	for i=maxselected+1,#checkboxes do
		if checkboxes[i].checked and not assignIndex(i) then break end
	end
	
	for i=1,maxselected do
		if self.squadIndices[i] == nil then
			self.squadIndices[i] = i
		end
	end
end

modApi:init()
mod_loader:init()