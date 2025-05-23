#include "cbrm_pch.h"

#include "VertexArray.h"

#ifdef CBRM_PLATFORM_WINDOWS
    #include "Cabrium/Platform/OpenGL/OpenGLVertexArray.h"
#else
    #error Platform not supported
#endif

namespace cabrium {

IVertexArray *IVertexArray::create() {

#ifdef CBRM_PLATFORM_WINDOWS
    return new opengl::VertexArray();
#else
    CBRM_CORE_ASSERT(0);
#endif
}

} // namespace cabrium
