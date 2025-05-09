#pragma once

namespace cabrium {

// class MouseButtonEvent : public Event {
// public:
//     MouseButtonEvent() {}
//
//     DECL_EVENT_CLASS_TYPE(WindowClose)
//     DECL_EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput |
//                               EventCategory::EventCategoryMouse |
//                               EventCategory::EventCategoryMouseButton)
// };

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

} // namespace cabrium