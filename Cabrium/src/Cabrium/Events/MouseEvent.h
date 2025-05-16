#pragma once

#include "Cabrium/Common/Mouse.h"
#include "Cabrium/Events/Event.h"

namespace cabrium {

class MouseButtonEvent : public Event {
public:
    mouse::ButtonCode getButtonCode() const { return button; }

    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryMouse |
                              EventCategory::EventCategoryMouseButton)
protected:
    MouseButtonEvent(const mouse::ButtonCode button_) : button(button_) {}

    mouse::ButtonCode button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(const mouse::ButtonCode button_) : MouseButtonEvent(button_) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << button;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(const mouse::ButtonCode button_) : MouseButtonEvent(button_) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << button;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(MouseButtonReleased)
};

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x_, float y_) : x(y_), y(y_) {}

    float getX() const { return x; }
    float getY() const { return y; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << x << ", " << y;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(MouseMoved)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryMouse)

private:
    float x, y;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float x_, float y_) : offset_x(x_), offset_y(y_) {}

    float getOffsetX() const { return offset_x; }
    float getOffsetY() const { return offset_y; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << offset_x << ", " << offset_y;
        return ss.str();
    }

    DECL_EVENT_CLASS_TYPE(MouseScrolled)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryMouse)

private:
    float offset_x, offset_y;
};

class MouseEnterEvent : public Event {
public:
    MouseEnterEvent(bool entered_) : entered(entered_) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseEnterEvent: " << entered;
        return ss.str();
    }

    bool getEntered() const { return entered; }

    DECL_EVENT_CLASS_TYPE(MouseEnter)
    DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse)

private:
    bool entered;
};

} // namespace cabrium