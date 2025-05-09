#include "Cabrium.h"

class Sandbox : public cabrium::Application {
public:
    Sandbox() {}
    ~Sandbox() {}
};

cabrium::Application *cabrium::createApplication() {

    // WindowResizeEvent e(1280, 720);

    // if (e.isInCategory(EventCategoryApplication)) {
    //     CBRM_TRACE(e);
    // }

    return new Sandbox();
}
