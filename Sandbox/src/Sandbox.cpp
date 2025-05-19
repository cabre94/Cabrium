#include <Cabrium.h>

#include "imgui.h"

class DummyLayer : public cabrium::Layer {
public:
    DummyLayer() : Layer("DummyLayer") {}

    void onUpdate() override {
        // CBRM_INFO("DummyLayer::onUpdate()");
        if (cabrium::Input::isKeyPressed(cabrium::key::Tab))
            CBRM_INFO("Tab pressed");
    }

    void onEvent(cabrium::Event &e) override {
        // CBRM_INFO("DummyLayer::onEvent - event {0}", 0);
    }

    void onImGuiRender() override {
        ImGui::Begin("DummyLayer");
        ImGui::Text("Hello DummyLayer");
        ImGui::End();
    }

private:
};

class Sandbox : public cabrium::Application {
public:
    Sandbox() {
        pushLayer(new DummyLayer());
        // pushLayer(new cabrium::ImGuiLayer());
    }
    ~Sandbox() {}
};

cabrium::Application *cabrium::createApplication() {
    //
    return new Sandbox();
}
