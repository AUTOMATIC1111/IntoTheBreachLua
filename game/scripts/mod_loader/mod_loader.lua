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

	if listdirs then
		local modlist = listdirs("mods")
		for key,value in pairs(modlist) do
			table.insert(self.mod_dirs,value)
		end
	else
		for dir in io.popen([[dir ".\mods\" /b /ad]]):lines() do table.insert(self.mod_dirs,dir) end
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

	local smallfont = sdl.filefont("resources/mods/JustinFont8.ttf",13);
	local screen = sdl.screen()
	local eventloop = sdl.eventloop()
	local w = screen:w()
	local h = screen:h()
	local quit = 0
	local pointer = sdl.scaled(2,sdl.surface("resources/mods/ui/pointer.png"));
	local mouserect = sdl.rect(sdl.mouse.x(), sdl.mouse.y(), pointer:w(), pointer:h())
	local screenshot = sdl.screenshot()
	local bg = sdl.rgba(0,0,0,128)

	local ui = UiRoot():widthpx(w):heightpx(h)
	
	-- bottom frame
	local framebot = Ui():width(0.4):heightpx(56):pos(0.4,0.7):padding(4):decorate({DecoFrame()})
	ui:add(framebot)

	local labelcount = Ui():pos(0,0):width(0.3):height(0.6):caption(""):decorate({DecoCaption()})
	framebot:add(labelcount)
	
	framebot:add(Ui():pos(0,0.6):width(0.3):height(0.4):caption("Total selected"):decorate({DecoCaption(smallfont)}))
	
	framebot:add(Ui():pos(0,1.35):width(1):height(0.4):caption("Hold SHIFT when starting new game to show this dialog again."):decorate({DecoCaption(smallfont)}))

	local buttongo = Ui():pos(0.3,0):width(0.7):height(1):caption("Continue"):decorate({DecoButton(),DecoCaption()})
	framebot:add(buttongo)
	buttongo.onclicked = function()
		quit = 1
	end
	
	-- top frame
	local frametop = Ui():width(0.6):height(0.575):pos(0.2,0.1):caption("Choose squads"):decorate({DecoFrame(), DecoFrameCaption()})
	ui:add(frametop)

	local scrollarea = UiScrollArea():width(1):height(1):padding(24):decorate({DecoSolid(sdl.rgb(24,28,40))})
	frametop:add(scrollarea)
	
	local checkboxes = {}
	local updatecount = function()
		local count = 0
		
		for i=1,#checkboxes do
			local checkbox = checkboxes[i]
			if checkbox.checked then count=count+1 end
		end
		
		labelcount:caption(count.."/"..maxselected);
		buttongo.disabled = count > maxselected
	end
	
	local rows = w < 1280 and 1 or 2
	
	for i=1,#modApi.squad_icon do
		local col = (i-1) % rows
		local row = math.floor((i-1) / rows)
		
		local checkbox = UiCheckbox():pos(0.5*col,-80*row):heightpx(41):width(rows == 1 and 1 or 0.48):decorate(
			{ DecoButton(), DecoCheckbox(), DecoSurfaceOutlined(sdl.surface(self.squad_icon[i])), DecoText(self.squad_text[(i-1)*2+1]) }
		)
		
		scrollarea:add( checkbox )
		
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
		
		screen:begin()
		screen:blit(screenshot, nil, 0, 0)
		screen:drawrect(bg, nil)
		ui:draw(screen)
		screen:blit(pointer, nil, mouserect.x, mouserect.y)
		screen:finish()
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

