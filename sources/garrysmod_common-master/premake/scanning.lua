function IncludeScanning()
	IncludePackage("scanning")

	local directory = _GARRYSMOD_COMMON_DIRECTORY .. "/include/scanning"

	local _project = project()
	local _workspace = _project.workspace
	local _project_directory = _GARRYSMOD_COMMON_DIRECTORY .. "/projects/" .. os.target() .. "/" .. _ACTION

	-- This first include directory is deprecated and might be removed in the future.
	sysincludedirs(directory)
	sysincludedirs(_GARRYSMOD_COMMON_DIRECTORY .. "/include")
	links("scanning")

	filter("system:macosx")
		links("CoreServices.framework")

	project("scanning")
		kind("StaticLib")
		language("C++")
		cppdialect("C++11")
		location(_GARRYSMOD_COMMON_DIRECTORY .. "/projects/" .. os.target() .. "/" .. _ACTION)
		sysincludedirs(directory)
		files({directory .. "/*.hpp", directory .. "/*.cpp"})
		vpaths({
			["Header files/*"] = directory .. "/*.hpp",
			["Source files/*"] = directory .. "/*.cpp"
		})

		filter("configurations:Release")
			objdir(_project_directory .. "/intermediate")
			targetdir(_project_directory .. "/release")

		if not _workspace.abi_compatible then
			filter("configurations:Debug")
				objdir(_project_directory .. "/intermediate")
				targetdir(_project_directory .. "/debug")
		end

		filter("system:linux or macosx")
			links("dl")

	project(_project.name)
end
