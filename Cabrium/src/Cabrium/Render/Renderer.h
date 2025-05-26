#pragma once

#include "Cabrium/Render/RenderAPI.h"
#include "Cabrium/Render/RenderCmd.h"

namespace cabrium {

class Renderer {

public:
    static void beginScene();
    static void endScene();
    static void submit(std::shared_ptr<IVertexArray> &va);

    // static void clear();

    // static void setClearColor(glm::vec4 &color);

    // static void drawIndexed(std::shared_ptr<IVertexArray> &va);

    // API getApi()  { return api; }

    // static RenderAPI::API getAPI() { return RenderAPI::getApi(); }

private:
    // stat
};

} // namespace cabrium