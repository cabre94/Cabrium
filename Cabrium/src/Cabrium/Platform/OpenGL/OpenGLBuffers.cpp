#include "cbrm_pch.h"

#include "OpenGLBuffers.h"

#include "Cabrium/Common/Assert.h"

#include <glad/glad.h>

namespace cabrium {

namespace opengl {

// -----------------------------------------
// ------------- VertexBuffer --------------
// -----------------------------------------

VertexBuffer::VertexBuffer(const void *data, uint32_t sz) {
    // glCreateBuffers(1, &render_id);

    glGenBuffers(1, &render_id);              // Get buffer id of the actual buffer
    glBindBuffer(GL_ARRAY_BUFFER, render_id); // Slect the buffer
    // bind();
    glBufferData(GL_ARRAY_BUFFER, sz, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &render_id); }

void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, render_id); }

void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

// -----------------------------------------
// -------------- IndexBuffer --------------
// -----------------------------------------

IndexBuffer::IndexBuffer(const uint32_t *data, uint32_t cnt) : idx_cnt(cnt) {
    CBRM_CORE_ASSERT(sizeof(GLuint) == sizeof(uint32_t), "sizeof(GLuint) == sizeof(uint32_t)");

    // glCreateBuffers(1, &render_id);
    glGenBuffers(1, &render_id);                      // Get buffer id of the actual buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id); // Slect the buffer
    // bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cnt * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &render_id); }

void IndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id); }

void IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

uint32_t IndexBuffer::getIndexCnt() const { return idx_cnt; }

} // namespace opengl

} // namespace cabrium
