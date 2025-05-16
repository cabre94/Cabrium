#pragma once

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/Layer.h"
#include "Cabrium/Events/KeyEvent.h"
#include "Cabrium/Events/MouseEvent.h"
#include "Cabrium/Events/WindowEvent.h"

// #include <imgui.h>

namespace cabrium {

class CBRM_API ImGuiLayer : public Layer {
public:
    ImGuiLayer() : Layer("ImGui-Layer") {}
    virtual ~ImGuiLayer() {}

    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onUpdate() override;
    virtual void onEvent(Event &event) override;

    void begin();
    void end();

private:
    // ImGui_ImplGlfw_WindowFocusCallback(GLFWwindow *window, int focused);      // Since 1.84
    bool onWindowFocusEvent(const WindowFocusEvent &event);

    // ----- ImGui_ImplGlfw_CursorEnterCallback(GLFWwindow *window, int entered);      // Since 1.84
    bool onMouseEnterEvent(const MouseEnterEvent &event);

    // ----- ImGui_ImplGlfw_CursorPosCallback(GLFWwindow *window, double x, double y); // Since 1.87
    bool onMouseMovedEvent(const MouseMovedEvent &event);

    // ImGui_ImplGlfw_MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    bool onMouseButtonPressedEvent(const MouseButtonPressedEvent &event);
    bool onMouseButtonReleasedEvent(const MouseButtonReleasedEvent &event);

    // ----- ImGui_ImplGlfw_ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    bool onMouseScrolledEvent(const MouseScrolledEvent &event);

    // ImGui_ImplGlfw_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    bool onKeyPressedEvent(const KeyPressedEvent &event);
    bool onKeyReleasedEvent(const KeyReleasedEvent &event);

    // ImGui_ImplGlfw_CharCallback(GLFWwindow *window, unsigned int c);
    // ImGui_ImplGlfw_MonitorCallback(GLFWmonitor *monitor, int event);

    struct ImGuiData {

        // GLFWwindow *Window;
        // GlfwClientApi ClientApi;

        float time = 1.0f / 60.0f; // double Time;
        // GLFWwindow *MouseWindow;
        //  GLFWcursor *MouseCursors[ImGuiMouseCursor_COUNT];
        float last_mouse_pos[2];
        // bool InstalledCallbacks;
        // bool CallbacksChainForAllWindows;
        // char BackendPlatformName[32];
    };

    ImGuiData data;
};

} // namespace cabrium