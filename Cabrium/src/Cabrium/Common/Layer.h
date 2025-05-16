#pragma once

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Events/Event.h"

#include <string>

namespace cabrium {

#pragma warning(push)
#pragma warning(disable : 4251)

class CBRM_API Layer {
public:
    Layer(const std::string &name_) : name(name_) {}
    virtual ~Layer() {}

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onEvent(Event &event) {}

    inline const std::string getName() { return name; }

protected:
    std::string name;
};

#pragma warning(pop)

} // namespace cabrium
