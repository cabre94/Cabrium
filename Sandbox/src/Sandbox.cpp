#include <Cabrium.h>

class DummyLayer : public cabrium::Layer {
public:
    DummyLayer() : Layer("DummyLayer") {}

    void onUpdate() override {
        // CBRM_INFO("DummyLayer::onUpdate()");
    }

    void onEvent(cabrium::Event &e) override {
        // CBRM_INFO("DummyLayer::onEvent - event {0}", 0);
    }

private:
};

class Sandbox : public cabrium::Application {
public:
    Sandbox() {
        pushLayer(new DummyLayer());
        pushLayer(new cabrium::ImGuiLayer());
    }
    ~Sandbox() {}
};

cabrium::Application *cabrium::createApplication() {
    //
    return new Sandbox();
}
