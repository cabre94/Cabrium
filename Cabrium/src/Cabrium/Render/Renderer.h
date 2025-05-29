#pragma once

#include "Cabrium/Render/OrthographicCamera.h"
#include "Cabrium/Render/RenderAPI.h"
#include "Cabrium/Render/RenderCmd.h"
#include "Cabrium/Render/Shader.h"

#include <glm/glm.hpp>

namespace cabrium {

class Renderer {

public:
    static void beginScene(OrthographicCamera &camera);
    static void endScene();
    static void submit(const std::shared_ptr<Shader> &shader, std::shared_ptr<IVertexArray> &va,
                       const glm::mat4 &transform = glm::mat4{1.0f});

    // static void clear();

    // static void setClearColor(glm::vec4 &color);

    // static void drawIndexed(std::shared_ptr<IVertexArray> &va);

    // API getApi()  { return api; }

    // static RenderAPI::API getAPI() { return RenderAPI::getApi(); }

private:
    // stat
    // OrthographicCamera &camera;

    struct SceneData {
        glm::mat4 view_proj_matrix;
    };

    static SceneData *scene_data;
};

} // namespace cabrium