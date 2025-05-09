#pragma once

#include "Cabrium/Events/Event.h"

namespace cabrium {

class AppTickEvent : public Event {
public:
    AppTickEvent() {}

    DECL_EVENT_CLASS_TYPE(AppTick)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class AppUpdateEvent : public Event {
public:
    AppUpdateEvent() {}

    DECL_EVENT_CLASS_TYPE(AppUpdate)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class AppRenderEvent : public Event {
public:
    AppRenderEvent() {}

    DECL_EVENT_CLASS_TYPE(AppRender)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

} // namespace cabrium