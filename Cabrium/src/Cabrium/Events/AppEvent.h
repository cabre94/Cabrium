#pragma once

#include "Cabrium/Events/Event.h"

namespace cabrium {

class AppTickEvent : public Event {
public:
    AppTickEvent() {}

    DECL_EVENT_CLASS_TYPE(AppTick)
    DECL_EVENT_CLASS_SOURCE(EventSource::EventSourceApplication)
};

class AppUpdateEvent : public Event {
public:
    AppUpdateEvent() {}

    DECL_EVENT_CLASS_TYPE(AppUpdate)
    DECL_EVENT_CLASS_SOURCE(EventSource::EventSourceApplication)
};

class AppRenderEvent : public Event {
public:
    AppRenderEvent() {}

    DECL_EVENT_CLASS_TYPE(AppRender)
    DECL_EVENT_CLASS_SOURCE(EventSource::EventSourceApplication)
};

} // namespace cabrium