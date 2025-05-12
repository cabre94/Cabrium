#pragma once

#include "Cabrium/Events/Event.h"

namespace cabrium {

class EventDispatcher {
public:
    EventDispatcher(Event &event_) : event(event_) {}

    template<typename T, typename F>
    bool dispatch(const F &func) {
        if (event.getEventType() != T::getStaticType())
            return false;

        event.handled |= func(static_cast<T &>(event));
        return true;
    }

private:
    Event &event;
};

} // namespace cabrium