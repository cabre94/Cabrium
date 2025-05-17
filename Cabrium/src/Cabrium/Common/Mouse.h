#pragma once

namespace cabrium {

namespace mouse {

enum ButtonCode : uint16_t {
    Button1      = 0,
    Button2      = 1,
    Button3      = 2,
    Button4      = 3,
    Button5      = 4,
    Button6      = 5,
    Button7      = 6,
    Button8      = 7,
    ButtonLast   = Button8,
    ButtonLeft   = Button1,
    ButtonRight  = Button2,
    ButtonMiddle = Button3
};

} // namespace mouse

// Maybe use a macro file with defines
/*
#ifdef USING GLFW
    #define CBRM_BUTTON1 GLFW_MOUSE_BUTTON_1
#elif USING_OTHER
    #define CBRM_BUTTON1 OTHER_MOUSE_BUTTON_1
#endif

// Then
enum ButtonCode : uint16_t {
    //...
    Button1 = CBRM_BUTTON1,
    // ...
};
*/

} // namespace cabrium