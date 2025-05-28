#pragma once

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/DeltaTime.h"
#include "Cabrium/Events/Event.h"

#include <string>

namespace cabrium {

class Layer {
public:
    Layer(const std::string &name_) : name(name_) {}
    virtual ~Layer() {}

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate(DeltaTime dt) {}
    virtual void onEvent(Event &event) {}

    virtual void onImGuiRender() {}

    inline const std::string getName() { return name; }

protected:
    std::string name;
};

} // namespace cabrium
