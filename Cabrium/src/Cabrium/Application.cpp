#include "cbrm_pch.h"

#include "Application.h"

namespace cabrium {

Application::Application() {}

Application::~Application() {}

void Application::run() {

    // WindowResizeEvent e(1280, 720);

    // if (e.isInCategory(EventCategoryApplication)) {
    //     CBRM_TRACE(e);
    // }

    while (getchar() != 'q')
        ;
}

} // namespace cabrium