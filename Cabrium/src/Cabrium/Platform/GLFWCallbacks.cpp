#include "cbrm_pch.h"

#include "WindowsWindow.h"

#include "Cabrium/Common/Log.h"
#include "Cabrium/Events/KeyEvent.h"
#include "Cabrium/Events/MouseEvent.h"
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

void WindowsWindow::setGLFWErrorCallback(int error_code, const char *description) {
    CBRM_CORE_ERROR("GLFW Error {0} {1}", error_code, description);
}

void WindowsWindow::setWindowSizeCallback(GLFWwindow *window, int width, int height) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);

    pData->props.width = width;
    pData->props.height = height;

    WindowResizeEvent event(width, height);
    pData->event_cb(event);
}

void WindowsWindow::setWindowCloseCallback(GLFWwindow *window) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);

    // if (!time_to_close)
    //     glfwSetWindowShouldClose(window, GLFW_FALSE);

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

// --------------------------------------
// -------- GLFW Mouse callbacks --------
// --------------------------------------

void WindowsWindow::setMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS) {
        // MouseButtonPressedEvent((mouse::ButtonCode) button);
        MouseButtonPressedEvent event((mouse::ButtonCode) button);
        pData->event_cb(event);

    } else if (action == GLFW_RELEASE) {
        MouseButtonReleasedEvent event((mouse::ButtonCode) button);
        pData->event_cb(event);
    } else {
        CBRM_CORE_ASSERT("WindowsWindow::setMouseButtonCallback - unexpected action value {}", action);
    }
}

void WindowsWindow::setScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    MouseScrolledEvent event(xoffset, yoffset);
    pData->event_cb(event);
}

void WindowsWindow::setCursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    MouseMovedEvent event(xpos, ypos);
    pData->event_cb(event);
}

void WindowsWindow::setCursorEnterCallback(GLFWwindow *window, int entered) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);
    MouseEnterEvent event(entered != 0);
    pData->event_cb(event);
}

void WindowsWindow::setKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Data *pData = (Data *) glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // MouseButtonPressedEvent((mouse::ButtonCode) button);
        KeyPressedEvent event((key::KeyCode) key, action == GLFW_REPEAT);
        pData->event_cb(event);
    } else if (action == GLFW_RELEASE) {
        KeyReleasedEvent event((key::KeyCode) key);
        pData->event_cb(event);
    } else {
        CBRM_CORE_ASSERT("WindowsWindow::setKeyCallback - unexpected action value {}", action);
    }
}

} // namespace cabrium