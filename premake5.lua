workspace "WorldEngine"
	architecture "x64"
	startproject "WorldEngine"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["SDL2"] = "WorldEngine/ThirdParty/SDL2/include"
IncludeDir["SDL2_Image"] = "WorldEngine/ThirdParty/SDL2_Image/include"
IncludeDir["GLEW"] = "WorldEngine/ThirdParty/GLEW/include"
IncludeDir["GLM"] = "WorldEngine/ThirdParty/GLM"

project "WorldEngine"
	location "WorldEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	
	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

	-- pchheader "wepch.h"
	-- pchsource "WorldEngine/src/wepch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	-- defines
	-- {
	-- 	"_CRT_SECURE_NO_WARNINGS"
	-- }

	-- Specify the include directories
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.SDL2_Image}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLM}"
	}


	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2test.lib",
		"SDL2_image.lib",
		"glew32.lib",
		"opengl32.lib",
		"Shell32.lib"
	}

	-- Specify the library directories
	libdirs
	{
		"WorldEngine/ThirdParty/SDL2/lib/x64",
		"WorldEngine/ThirdParty/SDL2_Image/lib/x64",
		"WorldEngine/ThirdParty/GLEW/lib/Release/x64"
	}
	
	-- Compiler settings
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "WE_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "WE_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "WE_DIST"
		runtime "Release"
		optimize "on"