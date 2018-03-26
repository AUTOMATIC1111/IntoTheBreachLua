require('scripts/sdlext/serizalize')
require('scripts/sdlext/extensions')
require('scripts/ui/ui')
require('scripts/sdlext/uieventloop')
require('scripts/sdlext/modcontent')
require('scripts/sdlext/pilotarrange')

sdlext.addModContent("Edit squads",function()
	modApi.selectSquads()
end)

arrangePilotsButton = sdlext.addModContent("Arrange pilots",function()
	showArrangePilotsUi()
end)
