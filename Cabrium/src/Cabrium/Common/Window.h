#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include "Cabrium/Events/Event.h"

namespace cabrium {

struct WindowProps {

    WindowProps(uint16_t width_ = 1920, uint16_t height_ = 1080, const std::string &title_ = "Cabrium")
        // WindowProps(uint16_t width_ = 1280, uint16_t height_ = 720, const std::string &title_ = "Cabrium")
        : width(width_), height(height_), title(title_) {}

    uint32_t width, height;
    std::string title;
};

class Window {
public:
    using eventCb = std::function<void(Event &)>;
    // using eventCb = void (*)(Event &);

    virtual ~Window() {}

    virtual void update() = 0;

    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;
    virtual void *getNativeWindow() const = 0;

    // Window attributes
    virtual void setEventCallback(const eventCb &cb) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;

    static Window *create(const WindowProps &props = WindowProps());

private:
};

} // namespace cabrium