#include "cbrm_pch.h"

#include "Application.h"

#include "Common/Log.h"
#include "Common/Window.h"
#include "Events/EventDispatcher.h"

// #include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace std::placeholders;

namespace cabrium {

// std::bind(&Application::onEvent, this, std::placeholders::_1);

Application *Application::instance = nullptr;

Application::Application() {
    CBRM_CORE_ASSERT(!instance, "Application::Application - already an instance");
    instance = this;

    // window = std::make_unique<Window>;
    window = std::unique_ptr<Window>(Window::create());

    window->setEventCallback(std::bind(&Application::onEvent, this, _1));
}

Application::~Application() {}

void Application::run() {

    while (running) {

        glClearColor(0, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer *layer : layer_list)
            layer->onUpdate();

        window->update();
    }
}

void Application::onEvent(Event &e) {
    CBRM_CORE_INFO("{0}", e);

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