#include "cbrm_pch.h"

#include "ImGuiLayer.h"

// #define IMGUI_IMPL_OPENGL_LOADER_GLAD
// #include <backends/imgui_impl_glfw.cpp>
//  #include <backends/imgui_impl_opengl3.cpp>

#include "Cabrium/Application.h"
#include "Cabrium/Common/Log.h"
#include "Cabrium/Events/EventDispatcher.h"
#include "Cabrium/Events/KeyEvent.h"
#include "Cabrium/Events/MouseEvent.h"
#include "Cabrium/Events/WindowEvent.h"
#include "Cabrium/Platform/OpenGL/GLFW_ImGui.h"
#include "Cabrium/Platform/OpenGL/OpenGL_ImGui.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

using namespace std::placeholders;

namespace cabrium {

void ImGuiLayer::onAttach() {
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    ImGuiIO &io = ImGui::GetIO();
    //(void) io;

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Keymaps

    //
    // GLFWwindow *w = glfwGetCurrentContext();
    Application &app = Application::getInstance();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void ImGuiLayer::onDetach() {}

void ImGuiLayer::onUpdate() {
    // CBRM_CORE_INFO("ImGuiLayer::onUpdate");

    Application &app = Application::getInstance();

    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float) app.getWindow().getWidth(), (float) app.getWindow().getHeight());
    // io.DisplaySize = ImVec2((float) 1080, (float) 720);

    float t = (float) glfwGetTime();
    // io.DeltaTime = (t - data.time);
    io.DeltaTime = data.time > 0.0f ? (t - data.time) : (1.0f / 60.0f);

    data.time = t;

    ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::Begin("Test");
    // ImGui::End();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(Event &event) {
    CBRM_CORE_INFO("ImGuiLayer::onEvent - {0}", event);

    EventDispatcher dispatcher(event);
    // dispatcher.dispatch<WindowFocusEvent>(std::bind(&ImGuiLayer::onWindowFocusEvent, this, _1));
    // dispatcher.dispatch<MouseEnterEvent>(std::bind(&ImGuiLayer::onMouseEnterEvent, this, _1));
    // dispatcher.dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::onMouseMovedEvent, this, _1));
    // dispatcher.dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::onMouseButtonPressedEvent, this, _1));
    // dispatcher.dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::onMouseButtonReleasedEvent, this, _1));
    // dispatcher.dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::onMouseScrolledEvent, this, _1));
    //  dispatcher.dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::onKeyPressedEvent, this, _1));
    //  dispatcher.dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::onKeyReleasedEvent, this, _1));
}

bool ImGuiLayer::onWindowFocusEvent(const WindowFocusEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onWindowFocusEvent");

    ImGuiIO &io = ImGui::GetIO();
    io.AddFocusEvent(event.getFocused() != 0);

    // io.AppFocusLost = !event.getFocused();

    return false;
}

bool ImGuiLayer::onMouseEnterEvent(const MouseEnterEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseEnterEvent");

    ImGuiIO &io = ImGui::GetIO();

    // ImVec2 new_pos;
    if (event.getEntered()) {
        // data->MouseWindow = window;
        // io.AddMousePosEvent(data.last_mouse_pos.x, data.last_mouse_pos.y);
        io.AddMousePosEvent(data.last_mouse_pos[0], data.last_mouse_pos[1]);

        // new_pos = ImVec2(data.last_mouse_pos[0], data.last_mouse_pos[1]);
        // } else if (!entered && bd->MouseWindow == window) {
    } else {
        data.last_mouse_pos[0] = io.MousePos.x;
        data.last_mouse_pos[1] = io.MousePos.y;
        // bd->MouseWindow = nullptr;
        // io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
        io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
        // new_pos = ImVec2(-FLT_MAX, -FLT_MAX);
    }

    // ImVec2 event_pos(e->MousePos.PosX, e->MousePos.PosY);
    // io.MousePos = new_pos;
    // io.MouseSource = e->MousePos.MouseSource;

    // return true;
    return false;
}

bool ImGuiLayer::onMouseMovedEvent(const MouseMovedEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseMovedEvent");

    ImGuiIO &io = ImGui::GetIO();
    float x = event.getX(), y = event.getY();

    //  data.last_mouse_pos = ImVec2(x, y);
    data.last_mouse_pos[0] = x;
    data.last_mouse_pos[1] = y;
    io.AddMousePosEvent(x, y);

    // io.MousePos = ImVec2(x, y);
    //  return true;
    return false;
}

bool ImGuiLayer::onMouseButtonPressedEvent(const MouseButtonPressedEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseButtonPressedEvent");

    ImGuiIO &io = ImGui::GetIO();

    mouse::ButtonCode button = event.getButtonCode();

    // if (button >= 0 && button < ImGuiMouseButton_COUNT)
    //     io.AddMouseButtonEvent((int) button, GLFW_PRESS);
    // io.AddMouseButtonEvent((int) button, GLFW_PRESS);
    io.AddMouseButtonEvent((int) button, true);

    // ImGuiInputEvent e;
    // e.Type = ImGuiInputEventType_MouseButton;
    // e.Source = ImGuiInputSource_Mouse;
    // e.EventId = g.InputEventsNextEventId++;
    // e.MouseButton.Button = mouse_button; button
    // e.MouseButton.Down = down; GLFW_PRESS
    // e.MouseButton.MouseSource = g.InputEventsNextMouseSource;
    // g.InputEventsQueue.push_back(e);

    // io.MouseDown[button] = true;
    //  io.MouseSource = e->MouseButton.MouseSource;

    return false;
}

bool ImGuiLayer::onMouseButtonReleasedEvent(const MouseButtonReleasedEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseButtonReleasedEvent");

    ImGuiIO &io = ImGui::GetIO();

    mouse::ButtonCode button = event.getButtonCode();

    // if (button >= 0 && button < ImGuiMouseButton_COUNT)
    //     io.AddMouseButtonEvent((int) button, GLFW_RELEASE);
    // io.AddMouseButtonEvent((int) button, GLFW_RELEASE);
    io.AddMouseButtonEvent((int) button, false);

    // io.MouseDown[button] = false;

    return false;
}

bool ImGuiLayer::onMouseScrolledEvent(const MouseScrolledEvent &event) {
    CBRM_CORE_TRACE("ImGuiLayer::onMouseScrolledEvent");

    ImGuiIO &io = ImGui::GetIO();

    io.AddMouseWheelEvent(event.getOffsetX(), event.getOffsetY());

    // io.MouseWheel += event.getOffsetX();
    // io.MouseWheelH += event.getOffsetY();

    return false;
}

// TODO: Remove--------------------------------------------
static int ImGui_ImplGlfw_TranslateUntranslatedKey(int key, int scancode) {

    if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_EQUAL)
        return key;
    GLFWerrorfun prev_error_callback = glfwSetErrorCallback(nullptr);
    const char *key_name = glfwGetKeyName(key, scancode);
    glfwSetErrorCallback(prev_error_callback);
#if GLFW_HAS_GETERROR && !defined(EMSCRIPTEN_USE_EMBEDDED_GLFW3) // Eat errors (see #5908)
    (void) glfwGetError(nullptr);
#endif
    if (key_name && key_name[0] != 0 && key_name[1] == 0) {
        const char char_names[] = "`-=[]\\,;\'./";
        const int char_keys[] = {GLFW_KEY_GRAVE_ACCENT,  GLFW_KEY_MINUS,     GLFW_KEY_EQUAL, GLFW_KEY_LEFT_BRACKET,
                                 GLFW_KEY_RIGHT_BRACKET, GLFW_KEY_BACKSLASH, GLFW_KEY_COMMA, GLFW_KEY_SEMICOLON,
                                 GLFW_KEY_APOSTROPHE,    GLFW_KEY_PERIOD,    GLFW_KEY_SLASH, 0};
        IM_ASSERT(IM_ARRAYSIZE(char_names) == IM_ARRAYSIZE(char_keys));
        if (key_name[0] >= '0' && key_name[0] <= '9') {
            key = GLFW_KEY_0 + (key_name[0] - '0');
        } else if (key_name[0] >= 'A' && key_name[0] <= 'Z') {
            key = GLFW_KEY_A + (key_name[0] - 'A');
        } else if (key_name[0] >= 'a' && key_name[0] <= 'z') {
            key = GLFW_KEY_A + (key_name[0] - 'a');
        } else if (const char *p = strchr(char_names, key_name[0])) {
            key = char_keys[p - char_names];
        }
    }
    // if (action == GLFW_PRESS) printf("key %d scancode %d name '%s'\n", key, scancode, key_name);
    return key;
}

static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode) {
    IM_UNUSED(scancode);
    switch (keycode) {
        case GLFW_KEY_TAB:
            return ImGuiKey_Tab;
        case GLFW_KEY_LEFT:
            return ImGuiKey_LeftArrow;
        case GLFW_KEY_RIGHT:
            return ImGuiKey_RightArrow;
        case GLFW_KEY_UP:
            return ImGuiKey_UpArrow;
        case GLFW_KEY_DOWN:
            return ImGuiKey_DownArrow;
        case GLFW_KEY_PAGE_UP:
            return ImGuiKey_PageUp;
        case GLFW_KEY_PAGE_DOWN:
            return ImGuiKey_PageDown;
        case GLFW_KEY_HOME:
            return ImGuiKey_Home;
        case GLFW_KEY_END:
            return ImGuiKey_End;
        case GLFW_KEY_INSERT:
            return ImGuiKey_Insert;
        case GLFW_KEY_DELETE:
            return ImGuiKey_Delete;
        case GLFW_KEY_BACKSPACE:
            return ImGuiKey_Backspace;
        case GLFW_KEY_SPACE:
            return ImGuiKey_Space;
        case GLFW_KEY_ENTER:
            return ImGuiKey_Enter;
        case GLFW_KEY_ESCAPE:
            return ImGuiKey_Escape;
        case GLFW_KEY_APOSTROPHE:
            return ImGuiKey_Apostrophe;
        case GLFW_KEY_COMMA:
            return ImGuiKey_Comma;
        case GLFW_KEY_MINUS:
            return ImGuiKey_Minus;
        case GLFW_KEY_PERIOD:
            return ImGuiKey_Period;
        case GLFW_KEY_SLASH:
            return ImGuiKey_Slash;
        case GLFW_KEY_SEMICOLON:
            return ImGuiKey_Semicolon;
        case GLFW_KEY_EQUAL:
            return ImGuiKey_Equal;
        case GLFW_KEY_LEFT_BRACKET:
            return ImGuiKey_LeftBracket;
        case GLFW_KEY_BACKSLASH:
            return ImGuiKey_Backslash;
        case GLFW_KEY_WORLD_1:
            return ImGuiKey_Oem102;
        case GLFW_KEY_WORLD_2:
            return ImGuiKey_Oem102;
        case GLFW_KEY_RIGHT_BRACKET:
            return ImGuiKey_RightBracket;
        case GLFW_KEY_GRAVE_ACCENT:
            return ImGuiKey_GraveAccent;
        case GLFW_KEY_CAPS_LOCK:
            return ImGuiKey_CapsLock;
        case GLFW_KEY_SCROLL_LOCK:
            return ImGuiKey_ScrollLock;
        case GLFW_KEY_NUM_LOCK:
            return ImGuiKey_NumLock;
        case GLFW_KEY_PRINT_SCREEN:
            return ImGuiKey_PrintScreen;
        case GLFW_KEY_PAUSE:
            return ImGuiKey_Pause;
        case GLFW_KEY_KP_0:
            return ImGuiKey_Keypad0;
        case GLFW_KEY_KP_1:
            return ImGuiKey_Keypad1;
        case GLFW_KEY_KP_2:
            return ImGuiKey_Keypad2;
        case GLFW_KEY_KP_3:
            return ImGuiKey_Keypad3;
        case GLFW_KEY_KP_4:
            return ImGuiKey_Keypad4;
        case GLFW_KEY_KP_5:
            return ImGuiKey_Keypad5;
        case GLFW_KEY_KP_6:
            return ImGuiKey_Keypad6;
        case GLFW_KEY_KP_7:
            return ImGuiKey_Keypad7;
        case GLFW_KEY_KP_8:
            return ImGuiKey_Keypad8;
        case GLFW_KEY_KP_9:
            return ImGuiKey_Keypad9;
        case GLFW_KEY_KP_DECIMAL:
            return ImGuiKey_KeypadDecimal;
        case GLFW_KEY_KP_DIVIDE:
            return ImGuiKey_KeypadDivide;
        case GLFW_KEY_KP_MULTIPLY:
            return ImGuiKey_KeypadMultiply;
        case GLFW_KEY_KP_SUBTRACT:
            return ImGuiKey_KeypadSubtract;
        case GLFW_KEY_KP_ADD:
            return ImGuiKey_KeypadAdd;
        case GLFW_KEY_KP_ENTER:
            return ImGuiKey_KeypadEnter;
        case GLFW_KEY_KP_EQUAL:
            return ImGuiKey_KeypadEqual;
        case GLFW_KEY_LEFT_SHIFT:
            return ImGuiKey_LeftShift;
        case GLFW_KEY_LEFT_CONTROL:
            return ImGuiKey_LeftCtrl;
        case GLFW_KEY_LEFT_ALT:
            return ImGuiKey_LeftAlt;
        case GLFW_KEY_LEFT_SUPER:
            return ImGuiKey_LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT:
            return ImGuiKey_RightShift;
        case GLFW_KEY_RIGHT_CONTROL:
            return ImGuiKey_RightCtrl;
        case GLFW_KEY_RIGHT_ALT:
            return ImGuiKey_RightAlt;
        case GLFW_KEY_RIGHT_SUPER:
            return ImGuiKey_RightSuper;
        case GLFW_KEY_MENU:
            return ImGuiKey_Menu;
        case GLFW_KEY_0:
            return ImGuiKey_0;
        case GLFW_KEY_1:
            return ImGuiKey_1;
        case GLFW_KEY_2:
            return ImGuiKey_2;
        case GLFW_KEY_3:
            return ImGuiKey_3;
        case GLFW_KEY_4:
            return ImGuiKey_4;
        case GLFW_KEY_5:
            return ImGuiKey_5;
        case GLFW_KEY_6:
            return ImGuiKey_6;
        case GLFW_KEY_7:
            return ImGuiKey_7;
        case GLFW_KEY_8:
            return ImGuiKey_8;
        case GLFW_KEY_9:
            return ImGuiKey_9;
        case GLFW_KEY_A:
            return ImGuiKey_A;
        case GLFW_KEY_B:
            return ImGuiKey_B;
        case GLFW_KEY_C:
            return ImGuiKey_C;
        case GLFW_KEY_D:
            return ImGuiKey_D;
        case GLFW_KEY_E:
            return ImGuiKey_E;
        case GLFW_KEY_F:
            return ImGuiKey_F;
        case GLFW_KEY_G:
            return ImGuiKey_G;
        case GLFW_KEY_H:
            return ImGuiKey_H;
        case GLFW_KEY_I:
            return ImGuiKey_I;
        case GLFW_KEY_J:
            return ImGuiKey_J;
        case GLFW_KEY_K:
            return ImGuiKey_K;
        case GLFW_KEY_L:
            return ImGuiKey_L;
        case GLFW_KEY_M:
            return ImGuiKey_M;
        case GLFW_KEY_N:
            return ImGuiKey_N;
        case GLFW_KEY_O:
            return ImGuiKey_O;
        case GLFW_KEY_P:
            return ImGuiKey_P;
        case GLFW_KEY_Q:
            return ImGuiKey_Q;
        case GLFW_KEY_R:
            return ImGuiKey_R;
        case GLFW_KEY_S:
            return ImGuiKey_S;
        case GLFW_KEY_T:
            return ImGuiKey_T;
        case GLFW_KEY_U:
            return ImGuiKey_U;
        case GLFW_KEY_V:
            return ImGuiKey_V;
        case GLFW_KEY_W:
            return ImGuiKey_W;
        case GLFW_KEY_X:
            return ImGuiKey_X;
        case GLFW_KEY_Y:
            return ImGuiKey_Y;
        case GLFW_KEY_Z:
            return ImGuiKey_Z;
        case GLFW_KEY_F1:
            return ImGuiKey_F1;
        case GLFW_KEY_F2:
            return ImGuiKey_F2;
        case GLFW_KEY_F3:
            return ImGuiKey_F3;
        case GLFW_KEY_F4:
            return ImGuiKey_F4;
        case GLFW_KEY_F5:
            return ImGuiKey_F5;
        case GLFW_KEY_F6:
            return ImGuiKey_F6;
        case GLFW_KEY_F7:
            return ImGuiKey_F7;
        case GLFW_KEY_F8:
            return ImGuiKey_F8;
        case GLFW_KEY_F9:
            return ImGuiKey_F9;
        case GLFW_KEY_F10:
            return ImGuiKey_F10;
        case GLFW_KEY_F11:
            return ImGuiKey_F11;
        case GLFW_KEY_F12:
            return ImGuiKey_F12;
        case GLFW_KEY_F13:
            return ImGuiKey_F13;
        case GLFW_KEY_F14:
            return ImGuiKey_F14;
        case GLFW_KEY_F15:
            return ImGuiKey_F15;
        case GLFW_KEY_F16:
            return ImGuiKey_F16;
        case GLFW_KEY_F17:
            return ImGuiKey_F17;
        case GLFW_KEY_F18:
            return ImGuiKey_F18;
        case GLFW_KEY_F19:
            return ImGuiKey_F19;
        case GLFW_KEY_F20:
            return ImGuiKey_F20;
        case GLFW_KEY_F21:
            return ImGuiKey_F21;
        case GLFW_KEY_F22:
            return ImGuiKey_F22;
        case GLFW_KEY_F23:
            return ImGuiKey_F23;
        case GLFW_KEY_F24:
            return ImGuiKey_F24;
        default:
            return ImGuiKey_None;
    }
}
// TODO: Remove

bool ImGuiLayer::onKeyPressedEvent(const KeyPressedEvent &event) {

    // key::KeyCode keycode = event.getKeyCode();
    int keycode = (int) event.getKeyCode();

    int scancode = glfwGetKeyScancode(keycode);
    keycode = ImGui_ImplGlfw_TranslateUntranslatedKey(keycode, scancode);

    ImGuiIO &io = ImGui::GetIO();
    ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(keycode, scancode);
    io.AddKeyEvent(imgui_key, GLFW_PRESS);
    io.SetKeyEventNativeData(imgui_key, keycode, scancode); // To support legacy indexing (<1.87 user code)
    return false;
}

bool ImGuiLayer::onKeyReleasedEvent(const KeyReleasedEvent &event) {
    // key::KeyCode keycode = event.getKeyCode();
    int keycode = (int) event.getKeyCode();

    int scancode = glfwGetKeyScancode(keycode);
    keycode = ImGui_ImplGlfw_TranslateUntranslatedKey(keycode, scancode);

    ImGuiIO &io = ImGui::GetIO();
    ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(keycode, scancode);
    io.AddKeyEvent(imgui_key, GLFW_RELEASE);
    io.SetKeyEventNativeData(imgui_key, keycode, scancode); // To support legacy indexing (<1.87 user code)
    return false;
}

void ImGuiLayer::begin() {}

void ImGuiLayer::end() {}

} // namespace cabrium