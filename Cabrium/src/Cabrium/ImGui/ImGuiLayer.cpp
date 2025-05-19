#include "cbrm_pch.h"

#include "ImGuiLayer.h"

#include "Cabrium/Application.h"
#include "Cabrium/Common/Log.h"
#include "Cabrium/Events/EventDispatcher.h"
#include "Cabrium/Events/KeyEvent.h"
#include "Cabrium/Events/MouseEvent.h"
#include "Cabrium/Events/WindowEvent.h"

// #include "Cabrium/Platform/OpenGL/GLFW_ImGui.h"
// #include "Cabrium/Platform/OpenGL/OpenGL_ImGui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

using namespace std::placeholders;

namespace cabrium {

void ImGuiLayer::onAttach() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    ImGui::StyleColorsClassic();

    ImGuiIO &io = ImGui::GetIO();

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
    // ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding              = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    //
    // GLFWwindow *w = glfwGetCurrentContext();
    Application &app   = Application::getInstance();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::onDetach() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::onImGuiRender() {

    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

void ImGuiLayer::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::end() {

    Application &app = Application::getInstance();
    ImGuiIO &io      = ImGui::GetIO();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

} // namespace cabrium