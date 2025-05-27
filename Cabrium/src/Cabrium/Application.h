#pragma once

#include <memory>

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/LayerList.h"
#include "Cabrium/Common/Window.h"
#include "Cabrium/Events/AppEvent.h"
#include "Cabrium/Events/WindowEvent.h"
#include "Cabrium/ImGui/ImGuiLayer.h"

#include "Cabrium/Render/Buffers.h"
#include "Cabrium/Render/OrthographicCamera.h"
#include "Cabrium/Render/VertexArray.h"

// Remove
#include "Cabrium/Render/Shader.h"

namespace cabrium {

class Application {
public:
    Application();
    virtual ~Application();

    void run();

    void onEvent(Event &e);

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *layer);
    void popLayer(Layer *layer) { layer_list.popLayer(layer); }

    static Application &getInstance() { return *instance; }
    Window &getWindow() { return *window; }

private:
    bool onWindowCloseEvent(WindowCloseEvent &e);

    std::unique_ptr<Window> window;

    ImGuiLayer *imgui_layer;

    bool running = true;

    LayerList layer_list;

    std::shared_ptr<Shader> shader;
    std::shared_ptr<IVertexArray> vertex_arr;

    std::shared_ptr<Shader> square_shader;
    std::shared_ptr<IVertexArray> square_va;

    OrthographicCamera camera;

    static Application *instance;
};

// To be defined in a client
Application *createApplication();

} // namespace cabrium