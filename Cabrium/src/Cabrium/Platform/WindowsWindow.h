#pragma once

#include "Cabrium/Common/Window.h"

#include <GLFW/glfw3.h>

namespace cabrium {

class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps &props_) { init(props_); }
    virtual ~WindowsWindow() { shutdown(); }

    void update() override;

    uint32_t getWidth() override { return data.props.width; };
    uint32_t getHeight() override { return data.props.height; };

    void setEventCallback(const eventCb &cb) override { data.event_cb = cb; };

    void setVSync(bool enabled) override;
    bool isVSync() const override { return data.vSync; };

private:
    virtual void init(const WindowProps &props_);
    virtual void shutdown();

    GLFWwindow *window = nullptr;

    struct Data {
        WindowProps props;

        bool vSync = false;
        eventCb event_cb = nullptr;
    };

    Data data;

    inline static bool GLFW_initialized = false;

    // GLFW Windows callbacks
    // static void setWindowPosCallback(GLFWwindow *window, int xpos, int ypos);
    static void setWindowSizeCallback(GLFWwindow *window, int width, int height);
    static void setWindowCloseCallback(GLFWwindow *window);
    // static void setWindowRefreshCallback(GLFWwindow *window);
    // static void setWindowFocusCallback(GLFWwindow *window, int focused);
    // static void setWindowIconifyCallback(GLFWwindow *window, int iconified);
    // static void setWindowMaximizeCallback(GLFWwindow *window, int maximized);
    // static void setFramebufferSizeCallback(GLFWwindow *window, int width, int height);
    // static void setWindowContentScaleCallback(GLFWwindow *window, float xscale, float yscale);

    // Set GLFW mouse callbacks
    static void setMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void setScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    static void setCursorPosCallback(GLFWwindow *window, double xpos, double ypos);
};
//
// GLFWAPI glfwSetWindowRefreshCallback
// glfwSetWindowRefreshCallback(GLFWwindow *handle, glfwSetWindowRefreshCallback
// cbfun);
//
// GLFWAPI glfwSetWindowFocusCallback glfwSetWindowFocusCallback(GLFWwindow
// *handle,
//                                                       glfwSetWindowFocusCallback
//                                                       cbfun);
//
// GLFWAPI glfwSetWindowIconifyCallback
// glfwSetWindowIconifyCallback(GLFWwindow *handle, glfwSetWindowIconifyCallback
// cbfun);
//
// GLFWAPI glfwSetWindowMaximizeCallback
// glfwSetWindowMaximizeCallback(GLFWwindow *handle,
// glfwSetWindowMaximizeCallback cbfun);
//
// GLFWAPI GLFWframebuffersizefun glfwSetFramebufferSizeCallback;
//
// GLFWAPI GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback;

} // namespace cabrium