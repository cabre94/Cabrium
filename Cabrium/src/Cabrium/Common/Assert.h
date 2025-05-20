#pragma once

#include "Cabrium/Common/Log.h"

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