#include "cbrm_pch.h"

#include "WindowsInput.h"

#include "Cabrium/Application.h"

#include <GLFW/glfw3.h>

namespace cabrium {

Input *Input::instance = new WindowsInput();

bool WindowsInput::isKeyPressedPlatform(key::KeyCode key_code) {

    Application &app = Application::getInstance();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    int state = glfwGetKey(window, key_code);

    return state == GLFW_PRESS;
}

bool WindowsInput::isMouseButtonPressedPlatform(mouse::ButtonCode button_code) {

    Application &app = Application::getInstance();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    int state = glfwGetMouseButton(window, button_code);

    return state == GLFW_PRESS;
}

float WindowsInput::getMouseXPlatform() {

    Application &app = Application::getInstance();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    double x;
    glfwGetCursorPos(window, &x, nullptr);

    return (float) x;
}

float WindowsInput::getMouseYPlatform() {

    Application &app = Application::getInstance();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    double y;
    glfwGetCursorPos(window, nullptr, &y);

    return (float) y;
}

} // namespace cabrium