#include "cbrm_pch.h"

#include "RenderAPI.h"

namespace cabrium {

#ifdef CBRM_PLATFORM_WINDOWS
RenderAPI::API RenderAPI::api = RenderAPI::API::OpenGL;
#else
    #error Platform not supported
#endif // CBRM_PLATFORM_WINDOWS
} // namespace cabrium