#pragma once

#include <memory>

#include "Common/Basic.h"
#include "Common/LayerList.h"
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

    void pushLayer(Layer *layer) { layer_list.pushLayer(layer); }
    void popLayer(Layer *layer) { layer_list.popLayer(layer); }

private:
    bool onWindowCloseEvent(WindowCloseEvent &e);

    std::unique_ptr<Window> window;

    bool running = true;

    LayerList layer_list;
};

#pragma warning(pop)

// To be defined in a client
Application *createApplication();

} // namespace cabrium