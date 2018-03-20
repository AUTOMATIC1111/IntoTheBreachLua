local resourceDat = sdl.resourceDat("resources/resource.dat")
local resourceDatMtime = sdl.mtime("resources/resource.dat")
local function checkResource()
	local mtime = sdl.mtime("resources/resource.dat")
	if resourceDatMtime ~= mtime then
		resourceDatMtime = mtime
		resourceDat:reload()
	end
end

sdlext = {}

function sdlext.font(path,size)
	checkResource()
	
	local blob = sdl.blobFromResourceDat(resourceDat,path)
	if blob.length==0 then
		return sdl.filefont(path, size)
	end

	return sdl.filefontFromBlob(blob,size)
end

function sdlext.surface(path)
	checkResource()
	
	local blob = sdl.blobFromResourceDat(resourceDat,path)
	if blob.length==0 then
		return sdl.surface(path)
	end
	
	return sdl.surfaceFromBlob(blob)
end
