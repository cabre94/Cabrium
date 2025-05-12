#pragma once

#include <memory>

#include "Common/Basic.h"
#include "Common/Window.h"
#include "Events/AppEvent.h"

namespace cabrium {

class CBRM_API Application {
public:
    Application();
    virtual ~Application();

    void run();

    void onEvent(Event &e);

private:
    std::unique_ptr<Window> window;

    bool running = true;
};

// To be defined in a client
Application *createApplication();

} // namespace cabrium