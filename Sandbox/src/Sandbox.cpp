#include <Cabrium.h>

class DummyLayer : public cabrium::Layer {
public:
    DummyLayer() : Layer("DummyLayer") {}

    void onUpdate() override { CBRM_INFO("DummyLayer::onUpdate()"); }

    void onEvent(const cabrium::Event &e) override { CBRM_INFO("DummyLayer::onEvent - event {0}", 0); }

private:
};

class Sandbox : public cabrium::Application {
public:
    Sandbox() { pushLayer(new DummyLayer()); }
    ~Sandbox() {}
};

cabrium::Application *cabrium::createApplication() {

    // WindowResizeEvent e(1280, 720);

    // if (e.isInCategory(EventCategoryApplication)) {
    //     CBRM_TRACE(e);
    // }

    return new Sandbox();
}
