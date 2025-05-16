#include "cbrm_pch.h"

#include "ImGuiLayer.h"

#include "Cabrium/Application.h"
#include "Cabrium/Common/Log.h"
#include "Cabrium/Events/EventDispatcher.h"
#include "Cabrium/Events/KeyEvent.h"
#include "Cabrium/Events/MouseEvent.h"
#include "Cabrium/Events/WindowEvent.h"
#include "Cabrium/Platform/OpenGL/GLFW_ImGui.h"
#include "Cabrium/Platform/OpenGL/OpenGL_ImGui.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

using namespace std::placeholders;

namespace cabrium {

void ImGuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    ImGui::StyleColorsClassic();

    ImGuiIO &io = ImGui::GetIO();

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //
    // GLFWwindow *w = glfwGetCurrentContext();
    Application &app = Application::getInstance();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::onDetach() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::onUpdate() {
    // CBRM_CORE_INFO("ImGuiLayer::onUpdate");
    // Begin
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Application &app = Application::getInstance();
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float) app.getWindow().getWidth(), (float) app.getWindow().getHeight());

    float t = (float) glfwGetTime();
    io.DeltaTime = (t - data.time);
    // io.DeltaTime = data.time > 0.0f ? (t - data.time) : (1.0f / 60.0f);
    data.time = t;

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(Event &event) {
    CBRM_CORE_INFO("ImGuiLayer::onEvent - {0}", event);

    EventDispatcher dispatcher(event);
    // dispatcher.dispatch<WindowFocusEvent>(std::bind(&ImGuiLayer::onWindowFocusEvent, this, _1));
    // dispatcher.dispatch<MouseEnterEvent>(std::bind(&ImGuiLayer::onMouseEnterEvent, this, _1));
    // dispatcher.dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::onMouseMovedEvent, this, _1));
    // dispatcher.dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::onMouseButtonPressedEvent, this, _1));
    // dispatcher.dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::onMouseButtonReleasedEvent, this, _1));
    // dispatcher.dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::onMouseScrolledEvent, this, _1));
    //  dispatcher.dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::onKeyPressedEvent, this, _1));
    //  dispatcher.dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::onKeyReleasedEvent, this, _1));
}

bool ImGuiLayer::onWindowFocusEvent(const WindowFocusEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onWindowFocusEvent");

    ImGuiIO &io = ImGui::GetIO();
    io.AddFocusEvent(event.getFocused() != 0);

    return false;
}

bool ImGuiLayer::onMouseEnterEvent(const MouseEnterEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseEnterEvent");

    ImGuiIO &io = ImGui::GetIO();

    if (event.getEntered()) {
        io.AddMousePosEvent(data.last_mouse_pos[0], data.last_mouse_pos[1]);
    } else {
        data.last_mouse_pos[0] = io.MousePos.x;
        data.last_mouse_pos[1] = io.MousePos.y;
        io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
    }

    return false;
}

bool ImGuiLayer::onMouseMovedEvent(const MouseMovedEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseMovedEvent");

    ImGuiIO &io = ImGui::GetIO();
    float x = event.getX(), y = event.getY();

    data.last_mouse_pos[0] = x;
    data.last_mouse_pos[1] = y;
    io.AddMousePosEvent(x, y);

    return false;
}

bool ImGuiLayer::onMouseButtonPressedEvent(const MouseButtonPressedEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseButtonPressedEvent");

    ImGuiIO &io = ImGui::GetIO();

    mouse::ButtonCode button = event.getButtonCode();

    io.AddMouseButtonEvent((int) button, true);

    return false;
}

bool ImGuiLayer::onMouseButtonReleasedEvent(const MouseButtonReleasedEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseButtonReleasedEvent");

    ImGuiIO &io = ImGui::GetIO();

    mouse::ButtonCode button = event.getButtonCode();

    io.AddMouseButtonEvent((int) button, false);

    return false;
}

bool ImGuiLayer::onMouseScrolledEvent(const MouseScrolledEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseScrolledEvent");

    ImGuiIO &io = ImGui::GetIO();

    io.AddMouseWheelEvent(event.getOffsetX(), event.getOffsetY());

    return false;
}

#if 0
bool ImGuiLayer::onKeyPressedEvent(const KeyPressedEvent &event) {

    // key::KeyCode keycode = event.getKeyCode();
    int keycode = (int) event.getKeyCode();

    int scancode = glfwGetKeyScancode(keycode);
    keycode = ImGui_ImplGlfw_TranslateUntranslatedKey(keycode, scancode);

    ImGuiIO &io = ImGui::GetIO();
    ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(keycode, scancode);
    io.AddKeyEvent(imgui_key, GLFW_PRESS);
    io.SetKeyEventNativeData(imgui_key, keycode, scancode); // To support legacy indexing (<1.87 user code)
    return false;
}

bool ImGuiLayer::onKeyReleasedEvent(const KeyReleasedEvent &event) {
    // key::KeyCode keycode = event.getKeyCode();
    int keycode = (int) event.getKeyCode();

    int scancode = glfwGetKeyScancode(keycode);
    keycode = ImGui_ImplGlfw_TranslateUntranslatedKey(keycode, scancode);

    ImGuiIO &io = ImGui::GetIO();
    ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(keycode, scancode);
    io.AddKeyEvent(imgui_key, GLFW_RELEASE);
    io.SetKeyEventNativeData(imgui_key, keycode, scancode); // To support legacy indexing (<1.87 user code)
    return false;
}
#endif

void ImGuiLayer::begin() {}

void ImGuiLayer::end() {}

} // namespace cabrium