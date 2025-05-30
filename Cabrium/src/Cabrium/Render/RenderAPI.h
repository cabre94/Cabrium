#pragma once

#include "Cabrium/Common/Types.h"
#include "Cabrium/Render/VertexArray.h"

#include <glm/glm.hpp>

namespace cabrium {

class RenderAPI {

public:
    enum class API {
        None = 0,
        OpenGL,
    };

    // virtual void beginScene() const = 0;
    // virtual void endScene() const   = 0;
    // virtual void submit() const     = 0;

    virtual void clear() const = 0;

    virtual void setClearColor(const glm::vec4 &color) const = 0;

    virtual void drawIndexed(const Ref<IVertexArray> &va) const = 0;

    API getApi() const { return api; }

private:
    static API api;
};

} // namespace cabrium