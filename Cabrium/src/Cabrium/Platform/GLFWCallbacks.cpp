#include "cbrm_pch.h"

#include "WindowsWindow.h"

#include "Cabrium/Events/WindowEvent.h"

#include <GLFW/glfw3.h>

namespace cabrium {

// --------------------------------------
// ------- GLFW Windows callbacks -------
// --------------------------------------

// void WindowsWindow::setWindowPosCallback(GLFWwindow *window, int xpos, int ypos) {
//     Data *pData = (Data *) glfwGetWindowUserPointer(window);
//     // WindowCloseEvent event;
//     // pData->event_cb(event);
// }

void WindowsWindow::setWindowSizeCallback(GLFWwindow *window, int width, int height) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);

    pData->props.width = width;
    pData->props.height = height;

    WindowResizeEvent event(width, height);
    pData->event_cb(event);
}

void WindowsWindow::setWindowCloseCallback(GLFWwindow *window) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);

    WindowCloseEvent event;
    pData->event_cb(event);
}

#if 0
void WindowsWindow::setWindowRefreshCallback(GLFWwindow *window) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    // WindowCloseEvent event;
    // pData->event_cb(event);
}

void WindowsWindow::setWindowFocusCallback(GLFWwindow *window, int focused) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    // WindowCloseEvent event;
    // pData->event_cb(event);
}

void WindowsWindow::setWindowIconifyCallback(GLFWwindow *window, int iconified) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    // WindowCloseEvent event;
    // pData->event_cb(event);
}

void WindowsWindow::setWindowMaximizeCallback(GLFWwindow *window, int maximized) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    // WindowCloseEvent event;
    // pData->event_cb(event);
}

void WindowsWindow::setFramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    // WindowCloseEvent event;
    // pData->event_cb(event);
}

void WindowsWindow::setWindowContentScaleCallback(GLFWwindow *window, float xscale, float yscale) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    // WindowCloseEvent event;
    // pData->event_cb(event);
}
#endif

} // namespace cabrium