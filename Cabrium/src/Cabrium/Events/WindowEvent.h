#pragma once

#include "Cabrium/Events/Event.h"

#include <sstream>

namespace cabrium {

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {}

    DECL_EVENT_CLASS_TYPE(WindowClose)
    DECL_EVENT_CLASS_SOURCE(EventSource::EventSourceApplication)
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width_, uint32_t height_) : width(width_), height(height_) {}

    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << width << ", " << height;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(WindowResize)
    DECL_EVENT_CLASS_SOURCE(EventSource::EventSourceApplication)

private:
    uint32_t width, height;
};

class WindowFocusEvent : public Event {
public:
    WindowFocusEvent(int focused_) : focused(focused_) {}

    DECL_EVENT_CLASS_TYPE(WindowFocus)
    DECL_EVENT_CLASS_SOURCE(EventSource::EventSourceApplication)

    int getFocused() const { return focused; }

private:
    int focused;
};

} // namespace cabrium