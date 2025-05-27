#include "cbrm_pch.h"

#include "Renderer.h"

#include "Cabrium/Render/RenderCmd.h"

namespace cabrium {

Renderer::SceneData *Renderer::scene_data = new Renderer::SceneData;

void Renderer::beginScene(OrthographicCamera &camera) {

    scene_data->view_proj_matrix = camera.getViewProjectionMatrix();
}

void Renderer::endScene() {}

void Renderer::submit(const std::shared_ptr<Shader> &shader, std::shared_ptr<IVertexArray> &va) {
    // shader
    shader->bind();
    shader->setUnirformMatrix4f("view_proj", scene_data->view_proj_matrix);

    // vertex array
    va->bind();

    RenderCmd::drawIndexed(va);
}

} // namespace cabrium