#pragma once

#include "Cabrium/Render/RenderAPI.h"
#include "Cabrium/Render/VertexArray.h"

namespace cabrium {

class RenderCmd {
public:
    static void clear() { render_api->clear(); }

    static void setClearColor(const glm::vec4 &color) { render_api->setClearColor(color); }

    static void drawIndexed(const std::shared_ptr<IVertexArray> &va) {
        render_api->drawIndexed(va);
    }

private:
    static RenderAPI *render_api;
};

} // namespace cabrium