#pragma once

#ifdef CABRIUM_PLATFORM_WINDOWS
	#ifdef CABRIUM_BUILD_DLL
		#define CABRIUM_API __declspec(dllexport)
	#else
		#define CABRIUM_API __declspec(dllimport)
	#endif	// CABRIUM_BUILD_DLL
#else
	#error Platform not supported
#endif	// CABRIUM_PLATFORM_WINDOWS