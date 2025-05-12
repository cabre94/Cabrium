#include "cbrm_pch.h"

#include "Application.h"

#include "Common/Log.h"
#include "Common/Window.h"
#include "Events/EventDispatcher.h"

#include <GLFW/glfw3.h>

using namespace std::placeholders;

namespace cabrium {

// std::bind(&Application::onEvent, this, std::placeholders::_1);

Application::Application() {
    // window = std::make_unique<Window>;
    window = std::unique_ptr<Window>(Window::create());

    window->setEventCallback(std::bind(&Application::onEvent, this, _1));
}

Application::~Application() {}

void Application::run() {

    // while (getchar() != 'q')
    //     ;

    while (running) {

        glClearColor(0, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        window->update();
    }
}

void Application::onEvent(Event &e) {
    CBRM_INFO("{0}", e);

    EventDispatcher dispatcher(e);

    dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowCloseEvent, this, _1));
}

bool Application::onWindowCloseEvent(WindowCloseEvent &e) {
    running = false;

    return true;
}

} // namespace cabrium