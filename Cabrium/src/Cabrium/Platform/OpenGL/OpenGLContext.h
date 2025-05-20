#pragma once

#include "Cabrium/Render/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace cabrium {

//
class OpenGLContext : public GraphicsContext {
public:
    OpenGLContext(GLFWwindow *window_);
    virtual ~OpenGLContext() = default;

    void init() override;
    void swapBuffers() override;

private:
    GLFWwindow *window;
};

} // namespace cabrium
