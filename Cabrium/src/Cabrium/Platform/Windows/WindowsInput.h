#pragma once

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/Input.h"

#include <GLFW/glfw3.h>

namespace cabrium {

class WindowsInput : public Input {
public:
    WindowsInput() {}
    ~WindowsInput() {}

protected:
    bool isKeyPressedPlatform(key::KeyCode key_code) override;

    // Inherited via Input
    bool isMouseButtonPressedPlatform(mouse::ButtonCode button_code) override;
    float getMouseXPlatform() override;
    float getMouseYPlatform() override;
};

} // namespace cabrium
