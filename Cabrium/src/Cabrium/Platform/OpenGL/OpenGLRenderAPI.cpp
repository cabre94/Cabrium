#include "cbrm_pch.h"

#include "OpenGLRenderAPI.h"

#include "Cabrium/Common/Types.h"

#include <glad\glad.h>

namespace cabrium {

// void OpenGLRenderAPI::beginScene() const {}
//
// void OpenGLRenderAPI::endScene() const {}
//
// void OpenGLRenderAPI::submit() const {}

void OpenGLRenderAPI::clear(/*TODO:flags*/) const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLRenderAPI::setClearColor(const glm::vec4 &color) const {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRenderAPI::drawIndexed(const Ref<IVertexArray> &va) const {
    glDrawElements(GL_TRIANGLES, va->getIndexBuffer()->getIndexCnt(), GL_UNSIGNED_INT, nullptr);
}

} // namespace cabrium