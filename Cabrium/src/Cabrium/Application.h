#pragma once

#include <memory>

#include "Common/Basic.h"
#include "Common/Window.h"

namespace cabrium {

class CBRM_API Application {
public:
    Application();
    virtual ~Application();

    void run();

private:
    std::unique_ptr<Window> window;

    bool running = true;
};

// To be defined in a client
Application *createApplication();

} // namespace cabrium