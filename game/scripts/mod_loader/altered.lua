----Add API functionality that changes existing content here----

oldGetPopulationTexts = GetPopulationTexts
local oldGetStartingSquad = getStartingSquad
local oldBaseNextTurn = Mission.BaseNextTurn
local oldBaseUpdate = Mission.BaseUpdate
local oldBaseStart = Mission.BaseStart
local oldGetText = GetText
local oldStartNewGame = startNewGame
local oldLoadGame = LoadGame

local selectSquadsTimer = sdl.timer()
function getStartingSquad(choice)
	local shiftdown = sdl.isshiftdown()
	local elapsed = selectSquadsTimer:elapsed()

	if modApi.squadIndices == nil or ((elapsed > 200) and shiftdown) then
		modApi:selectSquads()
		selectSquadsTimer = sdl.timer()
	end
	
	if choice >= 0 and choice <= 7 then
		local index = modApi.squadIndices[choice + 1]
		
		modApi:overwriteTextTrue("TipTitle_"..modApi.squadKeys[choice+1],modApi.squad_text[2 * (index-1) + 1])
		modApi:overwriteTextTrue("TipText_"..modApi.squadKeys[choice+1],modApi.squad_text[2 * (index-1) + 2])
		
		return modApi.mod_squads[index]
	else
		return oldGetStartingSquad(choice)
	end
end

function Mission:BaseNextTurn()
	oldBaseNextTurn(self)
	
	for i, hook in ipairs(modApi.nextTurnHooks) do
		hook(self)
	end
end

function Mission:BaseUpdate()
	oldBaseUpdate(self)
	
	for i, hook in ipairs(modApi.missionUpdateHooks) do
		hook(self)
	end
end

function Mission:MissionEnd()
	local ret = SkillEffect()
	
	CurrentMission = self
	EndingMission = true
	self.delayToAdd = 4
	for i, hook in ipairs(modApi.MissionEndHooks) do
		hook(self,ret)
	end
	ret:AddDelay(self:GetEndDelay())
	EndingMission = false
		
	Board:AddEffect(ret)
end

function Mission:BaseStart()
	for i, hook in ipairs(modApi.preMissionStartHooks) do
		hook(self)
	end
	
	oldBaseStart(self)
	
	for i, hook in ipairs(modApi.missionStartHooks) do
		hook(self)
	end
end

function Mission:GetEndDelay()
	return math.max(0,self.delayToAdd)
end

function GetText(id)
	if modApi.textOverrides and modApi.textOverrides[id] then
		return modApi.textOverrides[id]
	end
	
	return oldGetText(id)
end

function GetPopulationTexts(event, count)
    LOG(event)
	
	local nullReturn = count == 1 and "" or {}
	
	if modApi.PopEvents[event] == nil then
		return nullReturn
	end
	
	if Game == nil then
        return nullReturn
    end
	
	local list = copy_table(modApi.PopEvents[event])
	local ret = {}
	for i = 1, count do
		if #list == 0 then
			break
		end
		
		ret[#ret+1] = random_removal(list)
		
		
		if modApi.PopEvents[event].Odds ~= nil and random_int(100) > modApi.PopEvents[event].Odds then
			ret[#ret] = nil
		end
	end
	
	if #ret == 0 then
		return nullReturn
	end

	local corp_name = Game:GetCorp().bark_name
	local squad_name = Game:GetSquad()
	for i,v in ipairs(ret) do
		ret[i] = string.gsub(ret[i], "#squad", squad_name)
		ret[i] = string.gsub(ret[i], "#corp", corp_name)
		for j, fn in ipairs(modApi.onGetPopEvent) do
			ret[i] = fn(ret[i],ret,i,event,count)
		end
	end
	
	if count == 1 then
		return ret[1]
	end
	
	return ret
end

function startNewGame()
	--This should be replaced if/when we get the option to configure mod options from within the game
	--(either from a mods menu under the main menu or on a separate screen before the squad select screen like in Invisible, Inc.)
	local modOptions = mod_loader:getModContentDefaults()
	local savedOrder = {}--This should be replaced if/when we get the option to re-order mods
	
	--We have already loaded mods because we needed to do that before we entered the squad selection screen in order to show it correctly
	--mod_loader:loadModContent(modOptions,savedOrder)

	oldStartNewGame()
	
	GAME.modOptions = modOptions
	GAME.modLoadOrder = savedOrder
	GAME.squadTitles = {}
	
	for i, key in ipairs(modApi.squadKeys) do
		GAME.squadTitles["TipTitle_"..key] = GetText("TipTitle_"..key)
	end
end

function LoadGame()
	GAME.modOptions = GAME.modOptions or mod_loader:getModContentDefaults()
	GAME.modLoadOrder = GAME.modLoadOrder or {}

	mod_loader:loadModContent(GAME.modOptions,GAME.modLoadOrder)
	
	if GAME.squadTitles then
		for k, name in pairs(GAME.squadTitles) do
			modApi:overwriteTextTrue(k,name)
		end
	end

	oldLoadGame()
end