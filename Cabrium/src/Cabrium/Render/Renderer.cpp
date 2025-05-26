#include "cbrm_pch.h"

#include "Renderer.h"

#include "Cabrium/Render/RenderCmd.h"

namespace cabrium {

void Renderer::beginScene() {}

void Renderer::endScene() {}

void Renderer::submit(std::shared_ptr<IVertexArray> &va) {
    va->bind();

    RenderCmd::drawIndexed(va);
}

} // namespace cabrium