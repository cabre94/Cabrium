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

#ifdef CABRIUM_DEBUG
    #define CBRM_ENABLE_ASSERTS
#endif

#ifdef CBRM_ENABLE_ASSERTS
    #define CBRM_ASSERT(x, ...)                                   \
        {                                                         \
            if (!(x)) {                                           \
                CBRM_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                __debugbreak();                                   \
            }                                                     \
        }
    #define CBRM_CORE_ASSERT(x, ...)                                   \
        {                                                              \
            if (!(x)) {                                                \
                CBRM_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                __debugbreak();                                        \
            }                                                          \
        }
#else
    #define CBRM_ASSERT(...)
    #define CBRM_CORE_ASSERT(...)
#endif // CBRM_ENABLE_ASSERTS

#define BIT(x) (1 << x)