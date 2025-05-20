#pragma once

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/Layer.h"
#include "Cabrium/Events/KeyEvent.h"
#include "Cabrium/Events/MouseEvent.h"
#include "Cabrium/Events/WindowEvent.h"

namespace cabrium {

class ImGuiLayer : public Layer {
public:
    ImGuiLayer() : Layer("ImGui-Layer") {}
    virtual ~ImGuiLayer() {}

    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onImGuiRender() override;

    void begin();
    void end();

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