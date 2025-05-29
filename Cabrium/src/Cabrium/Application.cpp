#include "cbrm_pch.h"

#include "Application.h"

#include "Cabrium/Common/DeltaTime.h"
#include "Cabrium/Common/Input.h"
#include "Cabrium/Common/Log.h"
#include "Cabrium/Common/PlatformUtils.h"
#include "Cabrium/Common/Window.h"

#include "Cabrium/Events/EventDispatcher.h"

using namespace std::placeholders;

namespace cabrium {

Application *Application::instance = nullptr;

Application::Application() {
    CBRM_CORE_ASSERT(!instance, "Application::Application - already an instance");
    instance = this;

    window = std::unique_ptr<Window>(Window::create());
    window->setEventCallback(std::bind(&Application::onEvent, this, _1));

    imgui_layer = new ImGuiLayer();
    pushLayer(imgui_layer);
}

Application::~Application() {}

void Application::run() {

    float time;
    while (running) {

        time         = Time::getTime();
        DeltaTime dt = time - t_last_frame;
        t_last_frame = time;

        for (Layer *layer : layer_list)
            layer->onUpdate(dt);

        imgui_layer->begin();
        for (Layer *layer : layer_list)
            layer->onImGuiRender();
        imgui_layer->end();

        window->update();
    }
}

void Application::onEvent(Event &e) {
    CBRM_CORE_INFO("DummyLayer::onEvent - event {0}", e);

    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowCloseEvent, this, _1));

    for (auto it = layer_list.rbegin(); it != layer_list.rend(); ++it) {
        (*it)->onEvent(e);
        if (e.handled)
            break;
    }
}

void Application::pushLayer(Layer *layer) {
    layer_list.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer *layer) {
    layer_list.pushOverlay(layer);
    layer->onAttach();
}

bool Application::onWindowCloseEvent(WindowCloseEvent &e) {
    running = false;

    return true;
}

} // namespace cabrium