#pragma once

#include <memory>

#include "Common/Basic.h"
#include "Common/Window.h"
#include "Events/AppEvent.h"
#include "Events/WindowEvent.h"

namespace cabrium {

#pragma warning(push)
#pragma warning(disable : 4251)

class CBRM_API Application {
public:
    Application();
    virtual ~Application();

    void run();

    void onEvent(Event &e);

private:
    bool onWindowCloseEvent(WindowCloseEvent &e);

    std::unique_ptr<Window> window;

    bool running = true;
};

#pragma warning(pop)

// To be defined in a client
Application *createApplication();

} // namespace cabrium