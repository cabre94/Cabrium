workspace "Cabrium"
	architecture "x64"

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
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CBRM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CBRM_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "CBRM_DIST"
		symbols "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
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
		defines "CBRM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CBRM_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "CBRM_DIST"
		symbols "On"