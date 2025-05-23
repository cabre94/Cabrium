#pragma once

#ifdef CBRM_PLATFORM_WINDOWS
    #if 0
        #ifdef CBRM_BUILD_DLL
            #define CBRM_API __declspec(dllexport)
        #else
            #define CBRM_API __declspec(dllimport)
        #endif // CBRM_BUILD_DLL
    #endif
#else
    #error Platform not supported
#endif // CBRM_PLATFORM_WINDOWS

#define BIT(x) (1 << x)