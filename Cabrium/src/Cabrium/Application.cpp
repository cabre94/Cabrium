#include "cbrm_pch.h"

#include "Application.h"

#include "Common/Window.h"

#include <GLFW/glfw3.h>

namespace cabrium {

Application::Application() {
    // window = std::make_unique<Window>;
    window = std::unique_ptr<Window>(Window::create());
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

} // namespace cabrium