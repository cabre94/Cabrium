#pragma once

#include "Cabrium/Common/Window.h"

#include <GLFW/glfw3.h>

namespace cabrium {

class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps &props_) { init(props_); }
    virtual ~WindowsWindow() { shutdown(); }

    void update() override;

    uint32_t getWidth() override { return data.props.width; };
    uint32_t getHeight() override { return data.props.height; };

    void setEventCallback(const eventCb &cb) override { data.event_cb = cb; };

    void setVSync(bool enabled) override;
    bool isVSync() const override { return data.vSync; };

private:
    virtual void init(const WindowProps &props_);
    virtual void shutdown();

    GLFWwindow *window = nullptr;

    struct Data {
        WindowProps props;

        bool vSync = false;
        eventCb event_cb = nullptr;
    };

    Data data;

    inline static bool GLFW_initialized = false;
};

} // namespace cabrium