#include "Application.h"

#include <cstdio>

namespace cabrium {

Application::Application() {}

Application::~Application() {}

void Application::run() {

    while (getchar() != 'q')
        ;
}

} // namespace cabrium