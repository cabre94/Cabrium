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

    // Keymaps

    //
    // GLFWwindow *w = glfwGetCurrentContext();

    // ImGui_ImplGlfw_InitForOpenGL(w, true);
    ImGui_ImplOpenGL3_Init(nullptr);
}

void ImGuiLayer::onDetach() {}

void ImGuiLayer::onUpdate() {

    Application &app = Application::getInstance();

    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float) app.getWindow().getWidth(), (float) app.getWindow().getHeight());

    float t = glfwGetTime();
    io.DeltaTime = (t - time);
    time = t;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(const Event &event) {}

void ImGuiLayer::begin() {}

void ImGuiLayer::end() {}

} // namespace cabrium