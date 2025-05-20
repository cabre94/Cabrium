#pragma once

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/Key.h"
#include "Cabrium/Common/Mouse.h"

namespace cabrium {

class Input {
public:
    Input() {}
    ~Input() {}

    static bool isKeyPressed(key::KeyCode key_code) { return instance->isKeyPressedPlatform(key_code); }
    static bool isMouseButtonPressed(mouse::ButtonCode button_code) {
        return instance->isMouseButtonPressedPlatform(button_code);
    }
    static float getMouseX() { return instance->getMouseXPlatform(); }
    static float getMouseY() { return instance->getMouseYPlatform(); }

protected:
    virtual bool isKeyPressedPlatform(key::KeyCode key_code)                 = 0;
    virtual bool isMouseButtonPressedPlatform(mouse::ButtonCode button_code) = 0;

    virtual float getMouseXPlatform() = 0;
    virtual float getMouseYPlatform() = 0;

private:
    static Input *instance;
};

} // namespace cabrium
