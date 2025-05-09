#include "Application.h"

#include <cstdio>

namespace cabrium {

Application::Application() {}

Application::~Application() {}

void Application::Run() {

    while (getchar() != 'q')
        ;
}

} // namespace cabrium