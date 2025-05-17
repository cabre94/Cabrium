#pragma once

#include "Cabrium/Common/Basic.h"

#include <iostream>
#include <string>

namespace cabrium {

enum class EventType {
    None = 0,

    // Window events
    WindowClose,
    WindowResize,
    WindowFocus,
    // WindowLostFocus,
    // WindowMoved,

    // App events
    AppTick,
    AppUpdate,
    AppRender,

    // Keyboard events
    KeyPressed,
    KeyReleased,
    KeyTyped,

    // Mouse events
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
    MouseEnter,
};

enum EventSource : uint32_t {
    None = 0,
    EventSourceApplication = BIT(0),
    EventSourceInput = BIT(1),
    EventSourceKeyboard = BIT(2),
    EventSourceMouse = BIT(3),
    EventSourceMouseButton = BIT(4)
};

#define DECL_EVENT_CLASS_TYPE(type)                                             \
    static EventType getStaticType() { return EventType::type; }                \
    virtual EventType getEventType() const override { return getStaticType(); } \
    virtual const char *getName() const override { return #type; }

#define DECL_EVENT_CLASS_SOURCE(source) \
    virtual uint32_t getCategoryFlags() const override { return static_cast<uint32_t>(source); }

class Event {
public:
    virtual ~Event() {}

    virtual EventType getEventType() const = 0;
    virtual const char *getName() const = 0;
    virtual uint32_t getCategoryFlags() const = 0;
    virtual std::string toString() const { return getName(); };

    bool isInCategory(EventSource source) const { return getCategoryFlags() & static_cast<uint32_t>(source); }

    // private:
    bool handled = false;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e) { return os << e.toString(); }

inline std::string format_as(const Event &e) { return e.toString(); }

} // namespace cabrium