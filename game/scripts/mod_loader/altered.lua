----Add API functionality that changes existing content here----

local oldGetStartingSquad = getStartingSquad
local oldBaseNextTurn = Mission.BaseNextTurn
local oldBaseUpdate = Mission.BaseUpdate
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

function GetText(id)
	if modApi.textOverrides and modApi.textOverrides[id] then
		return modApi.textOverrides[id]
	end
	
	return oldGetText(id)
end

function startNewGame()
	oldStartNewGame()
	GAME.squadTitles = {}
	
	for i, key in ipairs(modApi.squadKeys) do
		GAME.squadTitles["TipTitle_"..key] = GetText("TipTitle_"..key)
	end
end

function LoadGame()
	oldLoadGame()
	if GAME.squadTitles then
		for k, name in pairs(GAME.squadTitles) do
			modApi:overwriteTextTrue(k,name)
		end
	end
end