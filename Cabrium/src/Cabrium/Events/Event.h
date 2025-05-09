#pragma once

#include "Cabrium/Core.h"

#include <cstdint>
#include <string>

namespace cabrium {

enum class EventType {
    None = 0,

    // Window events
    WindowClose,
    WindowResize,
    // WindowFocus,
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
    MouseButtonRealesed,
    MouseMoved,
    MouseScrolled,
};

enum EventCategory : uint32_t {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

// inline EventCategory operator|(EventCategory lhs, EventCategory rhs) {
//     return static_cast<EventCategory>(static_cast<EventCategory>(lhs) |
//                                       static_cast<EventCategory>(rhs));
// }
//
// inline EventCategory operator&(EventCategory lhs, EventCategory rhs) {
//     return static_cast<EventCategory>(static_cast<EventCategory>(lhs) &
//                                       static_cast<EventCategory>(rhs));
// }
//
// inline bool operator!(EventCategory category) {
//     return static_cast<std::underlying_type_t<EventCategory>>(category) == 0;
// }

#define DECL_EVENT_CLASS_TYPE(type)                                             \
    static EventType getStaticType() { return EventType::type; }                \
    virtual EventType getEventType() const override { return getStaticType(); } \
    virtual const char *getName() const override { return #type; }

#define DECL_EVENT_CLASS_CATEGORY(category) \
    virtual uint32_t getCategoryFlags() const override { return static_cast<uint32_t>(category); }

class Event {
public:
    virtual ~Event() {}

    virtual EventType getEventType() const = 0;
    virtual const char *getName() const = 0;
    virtual uint32_t getCategoryFlags() const = 0;
    virtual std::string toString() const { return getName(); };

    bool isInCategory(EventCategory category) const {
        return getCategoryFlags() & static_cast<uint32_t>(category);
    }

private:
    bool handled = false;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e) { return os << e.toString(); }

inline std::string format_as(const Event &e) { return e.toString(); }

} // namespace cabrium