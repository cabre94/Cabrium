#include "cbrm_pch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace cabrium {

// TODO: Move to other file
static GLenum shaderDataType2GLType(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Vec1:
        case ShaderDataType::Vec2:
        case ShaderDataType::Vec3:
        case ShaderDataType::Vec4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4: return GL_FLOAT;

        case ShaderDataType::Int1:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4: return GL_INT;

        case ShaderDataType::Bool: return GL_BOOL;

        case ShaderDataType::None:

        default:
            CBRM_CORE_ASSERT(false, "shaderDataType2GLType - invalid ShaderDataType");
            return 0;
    }
}

namespace opengl {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &render_id);
    // glBindVertexArray(render_id);
}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &render_id); }

void VertexArray::bind() const { glBindVertexArray(render_id); }

void VertexArray::unbind() const { glBindVertexArray(0); }

void VertexArray::addBuffer(const std::shared_ptr<IVertexBuffer> &v_buff) {
    // FIXME: How to check if layout has been set
    CBRM_CORE_ASSERT(v_buff->getLayout().getElements().size(),
                     "VertexArray::addBuffer vertex buffer has no layout")

    bind();
    v_buff->bind();

    uint32_t i         = 0;
    const auto &layout = v_buff->getLayout();
    for (const auto &element : layout) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.getCount(), shaderDataType2GLType(element.type),
                              element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(),
                              (const void *) element.offset);

        i++;
    }

    vertex_buff.push_back(v_buff);
}

void VertexArray::setIndexBuffer(const std::shared_ptr<IIndexBuffer> &i_buff) {
    bind();
    i_buff->bind();

    index_buff = i_buff;
}

const std::vector<std::shared_ptr<IVertexBuffer>> &VertexArray::getVextexBuffers() const {
    return vertex_buff;
}

const std::shared_ptr<IIndexBuffer> &VertexArray::getIndexBuffer() const { return index_buff; }

} // namespace opengl
} // namespace cabrium