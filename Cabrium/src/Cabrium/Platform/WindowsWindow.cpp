#include "cbrm_pch.h"

#include "WindowsWindow.h"

#include "Cabrium/Common/Log.h"

namespace cabrium {

// static bool WindowsWindow::GLFW_initialized = false;

// One implementation per platform
Window *Window::create(const WindowProps &props) {
    return new WindowsWindow(props);
}

void WindowsWindow::update() {
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

void WindowsWindow::setVSync(bool enabled) {

    // if (enabled) {
    //     glfwSwapInterval(1);
    // } else {
    //     glfwSwapInterval(0);
    // }

    glfwSwapInterval((int) enabled);

    data.vSync = enabled;
}

void WindowsWindow::init(const WindowProps &props_) {

    data.props = props_;

    CBRM_CORE_INFO("WindowsWindow::init {0} {1} {2}", data.props.title,
                   data.props.width, data.props.height);

    // Initialize GLFW in case is not initialized yet
    if (!GLFW_initialized) {
        int glfw_init_ok = glfwInit();
        CBRM_CORE_ASSERT(glfw_init_ok, "glfwInit failed!");

        GLFW_initialized = true;
    }
    // TODO: Need to manage multiple windows

    // if (!glfw_init_ok)
    //     return shutdown();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(data.props.width, data.props.height,
                              data.props.title.c_str(), NULL, NULL);
    if (!window) {
        return shutdown();
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, &data);
    setVSync(true);
}

void WindowsWindow::shutdown() {
    glfwDestroyWindow(window);
    window = nullptr;

    // glfwTerminate(); // TODO
}

} // namespace cabrium