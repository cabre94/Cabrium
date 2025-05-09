#pragma once

#include "Cabrium/Events/Event.h"

#include <cstdint>
#include <sstream>

namespace cabrium {

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {}

    DECL_EVENT_CLASS_TYPE(WindowCloseEvent)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width_, uint32_t height_) : width(width_), height(height_) {}

    uint32_t GetWidth() const { return width; }
    uint32_t GetHeight() const { return height; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << width << ", " << height;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(WindowResize)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

private:
    uint32_t width, height;
};

} // namespace cabrium