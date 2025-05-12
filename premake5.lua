workspace "Cabrium"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Cabrium/vendor/GLFW/include"

-- include premake file added on GLFW
include "Cabrium/vendor/GLFW"

project "Cabrium"
	location "Cabrium"
	kind "SharedLib"
	language "C++"

	-- for to use /MDd in premake: 
	-- staticruntime "off"
	-- runtime "Debug"
	-- /MTd in premake:
	-- staticruntime "on"
	-- runtime "Debug"
	staticruntime "on"

	buildoptions { "/utf-8" }

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("build/" .. outputdir .. "/%{prj.name}")

	pchheader "cbrm_pch.h"
	pchsource "Cabrium/src/cbrm_pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CBRM_PLATFORM_WINDOWS",
			"CBRM_BUILD_DLL"
		}

		postbuildcommands
		{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox/"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}

	filter "configurations:Debug"
		defines "CABRIUM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CABRIUM_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "CABRIUM_DIST"
		symbols "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	staticruntime "on"

	buildoptions { "/utf-8" }

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Cabrium/vendor/spdlog/include",
		"Cabrium/src"
	}

	links
	{
		"Cabrium"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CBRM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CABRIUM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CABRIUM_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "CABRIUM_DIST"
		symbols "On"