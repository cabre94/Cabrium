#include "cbrm_pch.h"

#include "Renderer.h"

#include "Cabrium/Platform/OpenGL/OpenGLShader.h"

#include "Cabrium/Render/RenderCmd.h"

namespace cabrium {

Renderer::SceneData *Renderer::scene_data = new Renderer::SceneData;

void Renderer::beginScene(OrthographicCamera &camera) {

    scene_data->view_proj_matrix = camera.getViewProjectionMatrix();
}

void Renderer::endScene() {}

void Renderer::submit(const std::shared_ptr<Shader> &shader, std::shared_ptr<IVertexArray> &va,
                      const glm::mat4 &transform) {
    shader->bind();
    // one pershader per scene
    std::dynamic_pointer_cast<OpenGLShader>(shader)->setUnirformMatrix4f(
        "view_proj", scene_data->view_proj_matrix);

    // transform need to be done one per object
    std::dynamic_pointer_cast<OpenGLShader>(shader)->setUnirformMatrix4f("transform", transform);

    va->bind(); // vertex array

    RenderCmd::drawIndexed(va);
}

} // namespace cabrium