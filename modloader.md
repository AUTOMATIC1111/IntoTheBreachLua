### init.lua
Each mod is defined by its init.lua file. This file must exist in `scripts/init.lua` path in your mod's root directory, or mod loader will be unable to load it.
The file, when executed, must return a table with following fields:

| Field | Description |
| --- | --- |
| id | Mod id. A string that is supposed to uniquely identify your mod, and shouldn't change as you release updates to it. |
| name | Name of the mod displayed to user. |
| version | A freeform string with mod's version. |
| requirements | A table with mod ids of other mods. This will cause those mods to load before yours.  |
| init | The init function. |
| load | The load function. |

Init function is called by mod loader first, followed by the call to load function.

Arguments for init function are:

| Argument | Description |
| --- | --- |
| self | The mod object. |

Arguments for load function are:

| Argument | Description |
| --- | --- |
| self | The mod object. |
| options | Mod options. Presumably a table. Possiblty not fully implemented yet. |
| version | Mod loader version. |

The `self` object, passed as first argument to both functions, is the table you previously returned from `init.lua` with following useful fields added:

| Field | Description |
| --- | --- |
| resourcePath | Path to mod's root directory. |
| scriptPath | Path to mod's root script directory - which should be equivalent to `self.resourcePath.."scripts/"`. |
| path | Path to mod's init.lua file. |
| dir | name of the mod's directory inside game's `mods` directory. |

Example:
```lua
local function init(self)
    LOG("Mod is being initialized!")
end

local function load(self,options,version)
    LOG("Mod is being loaded!")
end

return {
	id = "SampleMod",
	name = "Sample mod",
	version = "1.0.0",
	requirements = {},
	init = init,
	load = load,
}
```

### modApi:addSquad
`function modApi:addSquad(squad, name, desc, icon)`

Adds a new squad to the game.

| Argument | Description |
| --- | --- |
| squad | A table with 4 values - text identifier of the squad, followed by three mech text identifiers. Each mech mentioned must exist as a global variable, created similarly to game's mechs in `pawns.lua` file. |
| name | Name of the squad displayed to user. |
| desc | Description of the squad displayed to user. |
| icon | Icon used in custom squad selection UI. |

Example:
```lua
modApi:addSquad(
    { "Chess Squad", "AUTO_King", "AUTO_Knight", "AUTO_Rook" },
    "Chess Squad",
    "Chess piece themed mechs.",
    self.resourcePath.."/icon.png"
)
```

### modApi:overwriteText
`function modApi:overwriteText(id, str)`

**This description needs to be written.**

| Argument | Description |
| --- | --- |
| id | Text identifier to be replaced. |
| str | Replacement. |

### modApi:addPreMissionEndHook
`function modApi:addPreMissionEndHook(fn)`

Registers the function to be called before mission ends. **This description needs to be confirmed/clarified.**

| Argument | Description |
| --- | --- |
| fn | Function to be called when the event occurs. |

Example:
```lua
modApi:addPreMissionEndHook(function()
    LOG("We're here!")
end)
```

### modApi:addMissionStartHook
`function modApi:addMissionStartHook(fn)`

Registers the function to be called when the mission starts.

| Argument | Description |
| --- | --- |
| fn | Function to be called when the event occurs. |

### modApi:addNextTurnHook
`function modApi:addNextTurnHook(fn)`

Registers the function to be called when the turn starts. Both player and enemy have their own turns, so the function will be called twice after the user presses next turn button. Convenient built-in functions to call in the hook are `Game:GetTurnCount()`, which returns how many turns have passed,  and `Game:GetTeamTurn()`, which returns a value that can be compared to `TEAM_PLAYER` and `TEAM_ENEMY`

| Argument | Description |
| --- | --- |
| fn | Function to be called when the event occurs. |

Example:
```lua
modApi:addNextTurnHook(function()
    if Game:GetTeamTurn() == TEAM_PLAYER then
        LOG("This is shown at the beginning of your turn")
    end
end)
```

### modApi:addMissionUpdateHook
`function modApi:addMissionUpdateHook(fn)`

**This description needs to be written.**


### modApi:addMissionEndHook
`function modApi:addMissionEndHook(fn, i)`

**This description needs to be written.**

### modApi:addWeapon_Texts
`function modApi:addWeapon_Texts(tbl)`

Registers strings related to weapons with the game.

| Argument | Description |
| --- | --- |
| tbl | Table with as many key-value string pairs as you need. |

Weapons you create in mods are stored in global variables, and you use names of those variables to equip pawns. For every weapon, the game requires some strings to be defined, or can misbehave, or even crash. If a weapon is stored in vartable WeaponName, the game expects strings `WeaponName_Name` and `WeaponName_Description` to be registered. If a weapon has one upgrade, `WeaponName_Upgrade1` and `WeaponName_A_UpgradeDescription` must be registered, and with two upgrades, the game requires two more strings: `WeaponName_Upgrade2` and `WeaponName_B_UpgradeDescription`. The description for each string is in the table below.

| String | Description |
| --- | --- |
| WeaponName_Name | Name of the weapon displayed to user. |
| WeaponName_Description | Description of the weapon displayed to user. |
| WeaponName_Upgrade1 | Short description of the first upgrade. Make it less than about 12 characters, or it won't fit |
| WeaponName_A_UpgradeDescription | Long description of the first upgrade. |
| WeaponName_Upgrade2 | Short description of the second upgrade. Same restrictions apply. |
| WeaponName_B_UpgradeDescription | Long description of the second upgrade. |

Example:
```lua
modApi:addWeapon_Texts({
	AUTO_Rook_Cannon_Name = "Cross Cannons",
	AUTO_Rook_Cannon_Description = "Fires a projectile in all 4 directions, damaging and pushing on impact.",
	AUTO_Rook_Cannon_Upgrade1 = "Directional",
	AUTO_Rook_Cannon_A_UpgradeDescription = "Fire in three directions instead of four, with increased damage in one direction. Pushes self in the remaining direction.",
	AUTO_Rook_Cannon_Upgrade2 = "+1 Damage",
	AUTO_Rook_Cannon_B_UpgradeDescription = "Increases damage dealt by 1.",
	
	AUTO_Knight_Move_Name = "Knight Smite",
	AUTO_Knight_Move_Description = "Jumps to a location, killing any unit unfortunate enough to be there.",
})
```
A possibly more convenient way to use this function is to put all your weapon strings into a single file, `text_weapons.lua`:
```lua
return {
	AUTO_Rook_Cannon_Name = "Cross Cannons",
	AUTO_Rook_Cannon_Description = "Fires a projectile in all 4 directions, damaging and pushing on impact.",
	AUTO_Rook_Cannon_Upgrade1 = "Directional",
	AUTO_Rook_Cannon_A_UpgradeDescription = "Fire in three directions instead of four, with increased damage in one direction. Pushes self in the remaining direction.",
	AUTO_Rook_Cannon_Upgrade2 = "+1 Damage",
	AUTO_Rook_Cannon_B_UpgradeDescription = "Increases damage dealt by 1.",
	
	AUTO_Knight_Move_Name = "Knight Smite",
	AUTO_Knight_Move_Description = "Jumps to a location, killing any unit unfortunate enough to be there.",
}
```
And then add them to the game using:
```lua
modApi:addWeapon_Texts(require(self.scriptPath.."text_weapons"))
```

### modApi:addPopEvent
`function modApi:addPopEvent(event,msg)`

Registers PopEvent, the text shown near cities when certain actions happen ("The mechs are here, we're saved!", "Get away from the windows!").

| Argument | Description |
| --- | --- |
| event | Event id, text identifier specifying which exactly event is being extended. Possible values for event are: `"Opening"`, `"Closing"`, `"Closing_Dead"`, `"Closing_Perfect"`, `"Closing_Bad"`, `"Threatened"`, `"Killed"`, `"Shielded"`, `"Frozen"` |
| msg | Text displayed to user. Inside the string, `#squad` and `#corp` can be used to refer to current squad name and coropration name respectively. |

### modApi:setPopEventOdds
`function modApi:setPopEventOdds(event,odds)`

Sets the probability of the PopEvent occuring.

| Argument | Description |
| --- | --- |
| event | Event id |
| msg | A number from 0 to 100 indicating the probability of the PopEvent happening. |

### modApi:addOnPopEvent
`function modApi:addOnPopEvent(fn)`

Registers the function to be called when a PopEvent occurs. This function is called with 5 arguments, once for each text in the PopEvent.

| Argument | Description |
| --- | --- |
| fn | Function to be called when the event occurs. |

Arguments to the function are:

| Argument | Description |
| --- | --- |
| text | The text to be displayed to user. |
| texts | List of all texts registered for that event (and the first argumkent is one of them). |
| i | index of `text` in `texts` list. |
| event | Event id. |
| count | How many texts the game is expecting. |

The function should modify (or leave as it is) and return its first argument - the text displayed to user.

Example:
```lua
function modApi:addOnPopEvent(function(text,texts,i,event,count)
    return text.."!!!"
end)
```

### modApi:appendAsset
`function modApi:appendAsset(resource, filePath)`

Adds an asset (image or font) to the game (by putting it into `resources/resource.dat` file). All calls to this function must be inside your mod's `init` function.

| Argument | Description |
| --- | --- |
| resource | Path inside resource.dat where your asset should be placed. Use forward slahes (`/`). |
| filePath | Path to the asset in local filesystem. A common practice is to prepend `self.resourcePath` (which is the root directory of your mod) to the path. |

Example:
```lua
modApi:appendAsset("img/weapons/Whip.png",self.resourcePath.."/weapons/Whip.png")
```
