#pragma once

#include "Cabrium/Common/Layer.h"

namespace cabrium {

class ImGuiLayer : public Layer {
public:
    ImGuiLayer() : Layer("ImGui-Layer") {}
    virtual ~ImGuiLayer() {}

    virtual void onAttach() override;
    virtual void onDetach() override;
    // virtual void onUpdate() override;
    virtual void onEvent(const Event &event) override;

    void begin();
    void end();

private:
};

} // namespace cabrium