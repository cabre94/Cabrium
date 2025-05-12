#include "cbrm_pch.h"

#include "WindowsWindow.h"

#include "Cabrium/Events/WindowEvent.h"

#include <GLFW/glfw3.h>

namespace cabrium {

void WindowsWindow::setWindowPosCallback(GLFWwindow *window, int xpos, int ypos) {}

void WindowsWindow::setWindowSizeCallback(GLFWwindow *window, int width, int height) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);

    pData->props.width = width;
    pData->props.height = height;

    WindowResizeEvent event(width, height);
    pData->event_cb(event);
}
void WindowsWindow::setWindowCloseCallback(GLFWwindow *window) {}

void WindowsWindow::setWindowRefreshCallback(GLFWwindow *window) {}

void WindowsWindow::setWindowFocusCallback(GLFWwindow *window, int focused) {}

void WindowsWindow::setWindowIconifyCallback(GLFWwindow *window, int iconified) {}

void WindowsWindow::setWindowMaximizeCallback(GLFWwindow *window, int maximized) {}

void WindowsWindow::setFramebufferSizeCallback(GLFWwindow *window, int width, int height) {}

void WindowsWindow::setWindowContentScaleCallback(GLFWwindow *window, float xscale, float yscale) {}

} // namespace cabrium