#pragma once

#include "Cabrium/Common/Types.h"
#include "Cabrium/Render/RenderAPI.h"

namespace cabrium {

class OpenGLRenderAPI : public RenderAPI {
public:
    // void beginScene() const override;
    // void endScene() const override;
    // void submit() const override;
    void clear() const override;
    void setClearColor(const glm::vec4 &color) const override;
    void drawIndexed(const Ref<IVertexArray> &va) const override;
};

} // namespace cabrium
