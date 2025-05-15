#pragma once

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/Layer.h"

namespace cabrium {

class CBRM_API ImGuiLayer : public Layer {
public:
    ImGuiLayer() : Layer("ImGui-Layer") {}
    virtual ~ImGuiLayer() {}

    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onUpdate() override;
    virtual void onEvent(const Event &event) override;

    void begin();
    void end();

private:
    float time = 1.0f / 60.0f;
};

} // namespace cabrium