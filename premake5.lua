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
IncludeDir["glad"] = "Cabrium/vendor/glad/include"
IncludeDir["imgui"] = "Cabrium/vendor/imgui"
IncludeDir["glm"] = "Cabrium/vendor/glm"

-- include premake file added on GLFW
group "Dependencies"
	include "Cabrium/vendor/GLFW"
	include "Cabrium/vendor/glad"
	include "Cabrium/vendor/imgui"
group ""

project "Cabrium"
	location "Cabrium"
	kind "SharedLib"
	language "C++"

	staticruntime "off"


	-- for to use /MDd in premake: 
	-- staticruntime "off"
	-- runtime "Debug"
	-- /MTd in premake:
	-- staticruntime "on"
	-- runtime "Debug"
	-- staticruntime "on"

	buildoptions { "/utf-8" }

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("build/" .. outputdir .. "/%{prj.name}")

	pchheader "cbrm_pch.h"
	pchsource "Cabrium/src/cbrm_pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++20"
		-- staticruntime "On"
		systemversion "latest"

		defines
		{
			"CBRM_PLATFORM_WINDOWS",
			"CBRM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox/"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}

	filter "configurations:Debug"
		defines "CABRIUM_DEBUG"
		-- buildoptions "/MDd"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CABRIUM_RELEASE"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CABRIUM_DIST"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	-- staticruntime "on"
	-- On -> Sets RuntimeLibrary to Multithreaded
	-- Off -> Sets RuntimeLibrary to MultithreadedDLL
	staticruntime "off"

	buildoptions { "/utf-8" }

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Cabrium/vendor/spdlog/include",
		"Cabrium/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Cabrium"
	}

	filter "system:windows"
		cppdialect "c++20"
		--staticruntime "On"
		systemversion "latest"

		defines
		{
			"CBRM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CABRIUM_DEBUG"
		-- buildoptions "/MDd"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CABRIUM_RELEASE"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CABRIUM_DIST"
		-- buildoptions "/MD"
		runtime "Release"
		optimize "On"
