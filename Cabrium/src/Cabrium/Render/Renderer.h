#pragma once

#include "Cabrium/Common/Types.h"
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
    static void submit(const Ref<Shader> &shader, Ref<IVertexArray> &va,
                       const glm::mat4 &transform = glm::mat4{1.0f});

private:
    struct SceneData {
        glm::mat4 view_proj_matrix;
    };

    static SceneData *scene_data;
};

} // namespace cabrium