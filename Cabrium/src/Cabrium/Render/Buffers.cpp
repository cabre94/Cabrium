#include "cbrm_pch.h"

#include "Cabrium/Render/Buffers.h"

// #include "Cabrium/Platform/OpenGL/OpenGLBuffers.h"

// #include <glad/glad.h>

#ifdef CBRM_PLATFORM_WINDOWS
    #include "Cabrium/Platform/OpenGL/OpenGLBuffers.h"
#else
    #error Platform not supported
#endif

namespace cabrium {

IVertexBuffer *IVertexBuffer::create(const void *data, uint32_t sz) {

    // switch () {
    //	// choose renderAPI

#ifdef CBRM_PLATFORM_WINDOWS
    return new opengl::VertexBuffer(data, sz);
#else
    CBRM_CORE_ASSERT(0);
#endif
}

IIndexBuffer *IIndexBuffer::create(const uint32_t *idx, uint32_t cnt) {

#ifdef CBRM_PLATFORM_WINDOWS
    return new opengl::IndexBuffer(idx, cnt);
#else
    CBRM_CORE_ASSERT(0);
#endif
}

} // namespace cabrium