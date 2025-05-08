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

project "Cabrium"
	location "Cabrium"
	kind "SharedLib"
	language "C++"

	buildoptions { "/utf-8" }

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
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

	buildoptions { "/utf-8" }

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

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