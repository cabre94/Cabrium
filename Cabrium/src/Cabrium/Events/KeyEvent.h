#pragma once

#include "Cabrium/Common/Key.h"
#include "Cabrium/Events/Event.h"

namespace cabrium {

class KeyEvent : public Event {
public:
    key::KeyCode getKeyCode() const { return key; }

    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput |
                              EventCategory::EventCategoryKeyboard)
protected:
    KeyEvent(const key::KeyCode key_) : key(key_) {}

    key::KeyCode key;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(const key::KeyCode key_, bool repeated_ = false)
        : KeyEvent(key_), repeated(repeated_) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << key << " (repeat = " << repeated << ")";
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(KeyPressed)

private:
    bool repeated;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(const key::KeyCode key_) : KeyEvent(key_) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << key;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(const key::KeyCode key_) : KeyEvent(key_) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << key;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(KeyTyped)
};

} // namespace cabrium