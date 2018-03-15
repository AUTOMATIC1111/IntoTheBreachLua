-- This class serves mostly as a self-documenting guide to common mod operations,
-- as well as an indirection layer to maintain a kind of sanity for compatability purposes

local FtlDat = require("scripts/mod_loader/ftldat")

modApi = {}

local prev_path = package.path

local function file_exists(name)
   local f=io.open(name,"rb")
   if f~=nil then io.close(f) return true else return false end
end

function modApi:init()
	--package.path = prev_path..package.path
	self.version = "1.2.1"
	LOG("MOD-API VERSION "..self.version)
	self.currentModSquads = {}
	self.currentModSquadText = {}
	
	if not file_exists("resources/resource.dat.bak") then
		LOG("Backing up resource.dat")
	
		local from = io.open("resources/resource.dat","rb")
		local to = io.open("resources/resource.dat.bak","w+b")
		
		to:write(from:read("*all"))
		
		from:close()
		to:close()
	else
		local file = io.open("resources/resource.dat","rb")
		local inp = file:read("*all")
		file:close()
		local instance = FtlDat.FtlDat:from_string(inp)
		
		if not instance.signature then
			LOG("resource.dat has been updated since last launch, re-acquiring backup")
			
			local to = io.open("resources/resource.dat.bak","w+b")
			to:write(inp)
			to:close()
		else
			LOG("Restoring resource.dat")
		
			local from = io.open("resources/resource.dat.bak","rb")
			local to = io.open("resources/resource.dat","wb")
			
			to:write(from:read("*all"))
			
			from:close()
			to:close()
		end
	end
	
	modApi.resource = FtlDat.FtlDat:from_file("resources/resource.dat")
	
	self.squadKeys = {
		"Archive_A",
		"Rust_A",
		"Pinnacle_A",
		"Detritus_A",
		"Archive_B",
		"Rust_B",
		"Pinnacle_B",
		"Detritus_B",
	}
end

--Maintain sanity
--Update as new API functions are added
function modApi:resetModContent()
	self.textOverrides = {}
	self.mod_squads = {
		{"Rift Walkers","PunchMech", "TankMech", "ArtiMech"},
		{"Rusting Hulks","JetMech", "RocketMech",  "PulseMech"},
		{"Zenith Guard","LaserMech", "ChargeMech", "ScienceMech"},
		{"Blitzkrieg","ElectricMech", "WallMech", "RockartMech"},
		{"Steel Judoka","JudoMech", "DStrikeMech", "GravMech"},
		{"Flame Behemoths","FlameMech", "IgniteMech", "TeleMech"},
		{"Frozen Titans","GuardMech", "MirrorMech", "IceMech"},
		{"Hazardous Mechs","LeapMech", "UnstableTank", "NanoMech"},
	}
	self.squad_text = {
		"Rift Walkers",
		"These were the very first Mechs to fight against the Vek. They are efficient and reliable.",
		
		"Rusting Hulks",
		"R.S.T. weather manipulators allow these Mechs to take advantage of smoke storms everywhere.",
		
		"Zenith Guard",
		"Detritus' Beam technology and Pinnacle's Shield technology create a powerful combination.",
		
		"Blitzkrieg",
		"R.S.T. engineers designed this Squad around the mass destruction capabilities of harnessed lightning.",
		
		"Steel Judoka",
		"These Mechs specialize in positional manipulation to turn the Vek against each other.",
		
		
		"Flame Behemoths",
		"Invincible to flames, these Mechs aim to burn any threat to ashes.",
		
		
		"Frozen Titans",
		"These Titans rely on the Cryo Launcher, a powerful weapon that takes an experienced Pilot to master.",
		
		"Hazardous Mechs",
		"These Mechs have spectacular damage output but rely on nanobots feeding off dead Vek to stay alive.",
	}
	self.squad_icon = {
		"resources/mods/squads/mech_punch_ns.png",
		"resources/mods/squads/mech_jet_ns.png",
		"resources/mods/squads/mech_laser_ns.png",
		"resources/mods/squads/mech_electric_ns.png",
		"resources/mods/squads/mech_judo_ns.png",
		"resources/mods/squads/mech_flame_ns.png",
		"resources/mods/squads/mech_guard_ns.png",
		"resources/mods/squads/mech_leap_ns.png",
	}
	self.nextTurnHooks = {}
	self.missionUpdateHooks = {}
	self.missionStartHooks = {}
	self.preMissionStartHooks = {}
	self.currentModSquads = {}
	self.currentModSquadText = {}
	self.MissionEndHooks = {
		--Pilot Message
		function(mission,ret)
			ret:AddScript([[local ret = SkillEffect()
			local enemy_count = Board:GetEnemyCount()
			if enemy_count == 0 then
				ret:AddVoice("MissionEnd_Dead", -1)
			elseif self.RetreatEndingMessage then
				ret:AddVoice("MissionEnd_Retreat", -1)
			end
			Board:AddEffect(ret)]])
		end,
		
		--Population Event
		function(mission,ret)
			ret:AddScript([[local ret = SkillEffect()
			local enemy_count = Board:GetEnemyCount()
			
			if CurrentMission:GetDamage() == 0 then
				ret:AddScript("Board:StartPopEvent(\"Closing_Perfect\")")
			elseif CurrentMission:GetDamage() > 4 then
				ret:AddScript("Board:StartPopEvent(\"Closing_Bad\")")
			elseif enemy_count > 0 then
				ret:AddScript("Board:StartPopEvent(\"Closing\")")
			else
				ret:AddScript("Board:StartPopEvent(\"Closing_Dead\")")
			end
			Board:AddEffect(ret)]])
		end,
		
		--Enemy retreat
		function(mission,ret)
			ret:AddScript([[
			local ret = SkillEffect()
			local effect = SpaceDamage()
			effect.bEvacuate = true
			effect.fDelay = 0.5
			
			local board_size = Board:GetSize()
			for i = 0, board_size.x - 1 do
				for j = 0, board_size.y - 1  do
					if Board:IsPawnTeam(Point(i,j),TEAM_ENEMY)  then
						effect.loc = Point(i,j)
						ret:AddDamage(effect)
						CurrentMission.delayToAdd = CurrentMission.delayToAdd - 0.5
					end
				end
			end
			Board:AddEffect(ret)]])
		end,
		
		--End Delay
		function(mission,ret)
			ret:AddScript([[local ret = SkillEffect()
			--ret:AddDelay(CurrentMission:GetEndDelay())
			Board:AddEffect(ret)]])
		end,
	}
	self.iMePilotMessage = 1
	self.iMePopEvent = 2
	self.iMeRetreat = 3
	self.iMeDelay = 4
	
	local name, tbl = debug.getupvalue(oldGetPopulationTexts,1)
	self.PopEvents = copy_table(tbl)
	self.onGetPopEvent = {}
end

function modApi:setCurrentMod(mod)
	self.currentMod = mod
	self.currentModSquads[mod] = {}
	self.currentModSquadText[mod] = {}
end

--The updated way to add squads
function modApi:addSquadTrue(squad,name,desc,icon)
	assert(type(squad) == "table")
	assert(#squad == 4)
	assert(type(name) == "string")
	assert(type(desc) == "string")
	table.insert(self.mod_squads,squad)
	table.insert(self.squad_text,name)
	table.insert(self.squad_text,desc)
	table.insert(self.squad_icon,icon or "resources/mods/squads/unknown.png")
end

function modApi:addSquad(id,squad,desc,icon)
	if type(id) == "table" and type(squad) == "string" and type(desc) == "string" then
		return self:addSquadTrue(id,squad,desc,icon)
	end

	--The old way to add squads
	assert(id)
	assert(type(squad) == "table")
	assert(#squad == 4)
	--self.mod_squads[id] = squad
	local name
	local desc
	local text = self.currentModSquadText[self.currentMod][id]
	if text then
		if text[1] then
			name = text[1]
		end
		if text[2] then
			desc = text[2]
		end
	end
	
	self.currentModSquads[self.currentMod][id] = squad
	
	if name and desc then
		self:addSquadTrue(squad,name,desc,icon)
	end
end

function modApi:overwriteTextTrue(id,str)
	assert(type(id) == "string")
	assert(type(str) == "string")
	self.textOverrides[id] = str
end

function modApi:overwriteText(id,str)
	assert(type(id) == "string")
	assert(type(str) == "string")
	if id:sub(1,9) == "TipTitle_" then
		for i, key in pairs(self.squadKeys) do
			if id == "TipTitle_"..key then
				local text = self.currentModSquadText[self.currentMod][i - 1]
				if not text then
					text = {}
					self.currentModSquadText[self.currentMod][i - 1] = text
				end
				
				text[1] = str
				
				local squad = self.currentModSquads[self.currentMod][i - 1]
				local desc = text[2]
				
				if squad and desc then
					self:addSquadTrue(squad,str,desc)
				end
				
				return
			end
		end
	elseif id:sub(1,8) == "TipText_" then
		for i, key in pairs(self.squadKeys) do
			if id == "TipText_"..key then
				local text = self.currentModSquadText[self.currentMod][i - 1]
				if not text then
					text = {}
					self.currentModSquadText[self.currentMod][i - 1] = text
				end
				
				text[2] = str
				
				local squad = self.currentModSquads[self.currentMod][i - 1]
				local name = text[1]
				
				if squad and name then
					self:addSquadTrue(squad,name,str)
				end
				
				return
			end
		end
	end
	
	self.textOverrides[id] = str
end

function modApi:addPreMissionEndHook(fn)
	assert(type(fn) == "function")
	table.insert(self.preMissionStartHooks,fn)
end

function modApi:addMissionStartHook(fn)
	assert(type(fn) == "function")
	table.insert(self.missionStartHooks,fn)
end

function modApi:addNextTurnHook(fn)
	assert(type(fn) == "function")
	table.insert(self.nextTurnHooks,fn)
end

function modApi:addMissionUpdateHook(fn)
	assert(type(fn) == "function")
	table.insert(self.missionUpdateHooks,fn)
end

function modApi:addMissionEndHook(fn,i)
	assert(type(fn) == "function")
	if i ~= nil then
		assert(type(i) == "number")
		assert(i > 0)
		assert(math.floor(i) == i)
		table.insert(self.MissionEndHooks,i,fn)
		if i <= self.iMePilotMessage then
			self.iMePilotMessage = self.iMePilotMessage + 1
		end
		if i <= self.iMePopEvent then
			self.iMePopEvent = self.iMePopEvent + 1
		end
		if i <= self.iMeRetreat then
			self.iMeRetreat = self.iMeRetreat + 1
		end
		if i <= self.iMeDelay then
			self.iMeDelay = self.iMeDelay + 1
		end
	else
		table.insert(self.MissionEndHooks,fn)
	end
end

function modApi:addWeapon_Texts(tbl)
	assert(type(tbl) == "table")
	for k,v in pairs(tbl) do
		Weapon_Texts[k] = v
	end
end

function modApi:addPopEvent(event,msg)
	assert(type(event) == "string")
	assert(type(msg) == "string")
	if not self.PopEvents[event] then
		self.PopEvents[event] = {}
	end
	
	table.insert(self.PopEvents[event],msg)
end

function modApi:setPopEventOdds(event,odds)
	assert(type(event) == "string")
	assert(self.PopEvents[event])
	assert(odds == nil or type(odds) == "number")
	
	self.PopEvents[event].Odds = odds
end

function modApi:addOnPopEvent(fn)
	assert(type(fn) == "function")
	table.insert(self.onGetPopEvent,fn)
end

function modApi:appendAsset(resource,filePath)
	local f = io.open(filePath,"rb")
	assert(f,filePath)
	assert(type(resource) == "string")
	
	for i, file in ipairs(self.resource._files) do
		if file._meta._filename == resource then
			file._meta.body = f:read("*all")
			file._meta._fileSize = file._meta.body:len()
		
			return
		end
	end
	
	self.resource._numFiles = self.resource._numFiles + 1
	
	local file = FtlDat.File(self.resource._io,self.resource,self.resource.m_root)
	file._meta = FtlDat.Meta(file._io, file, file.m_root)
	
	file._meta._filenameSize = resource:len()
	file._meta._filename = resource
	file._meta.body = f:read("*all")
	file._meta._fileSize = file._meta.body:len()
    
    table.insert(self.resource._files,file)
end

function modApi:getSignature()
	return "ModLoaderSignature"
end

function modApi:finalize()
	local f = io.open("resources/resource.dat","wb")
	
	if not self.resource.signature then
		self.resource.signature = true
		self.resource._numFiles = self.resource._numFiles + 1
		local file = FtlDat.File(self.resource._io,self.resource,self.resource.m_root)
		file._meta = FtlDat.Meta(file._io, file, file.m_root)
		
		file._meta._filename = self:getSignature()
		file._meta._filenameSize = file._meta._filename:len()
		file._meta.body = "S"
		file._meta._fileSize = file._meta.body:len()
		table.insert(self.resource._files,file)
	end
	
	local output = self.resource:_write()
	f:write(output)
	f:close()
end