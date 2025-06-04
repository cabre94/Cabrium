#include "cbrm_pch.h"

#include "Texture.h"

#include "Cabrium/Platform/OpenGL/OpenGLTexture2D.h"

namespace cabrium {

Ref<Texture2D> Texture2D::create(const std::string &path) {
#ifdef CBRM_PLATFORM_WINDOWS
    return std::make_unique<OpenGLTexture2D>(path);
#else
    CBRM_CORE_ASSERT(0);
#endif
}

} // namespace cabrium
