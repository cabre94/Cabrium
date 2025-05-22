#include "cbrm_pch.h"

#include "Application.h"

#include "Cabrium/Common/Input.h"
#include "Cabrium/Common/Log.h"
#include "Cabrium/Common/Window.h"
#include "Cabrium/Events/EventDispatcher.h"

// Remove
#include "Cabrium/Render/Buffers.h"
#include "Cabrium/Render/Shader.h"

#include <glad/glad.h>

using namespace std::placeholders;

namespace cabrium {

// std::bind(&Application::onEvent, this, std::placeholders::_1);

Application *Application::instance = nullptr;

Application::Application() {
    CBRM_CORE_ASSERT(!instance, "Application::Application - already an instance");
    instance = this;

    // window = std::make_unique<Window>;
    window = std::unique_ptr<Window>(Window::create());

    window->setEventCallback(std::bind(&Application::onEvent, this, _1));

    // imgui_layer = std::make_unique<ImGuiLayer>();
    imgui_layer = new ImGuiLayer();
    pushLayer(imgui_layer);

    // shader

    // Vertex array
    glGenVertexArrays(1, &vertex_arr);
    // glCreateVertexArrays();
    glBindVertexArray(vertex_arr);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.0f,  0.5f,  0.0f  //
    };

    // Vertex buffer
    // vertex_buff =
    //    std::make_unique<IVertexBuffer>(IVertexBuffer::create(vertices, sizeof(vertices)));
    vertex_buff.reset(IVertexBuffer::create(vertices, sizeof(vertices)));

    vertex_buff->bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    // index buffer
    uint32_t idx[3] = {0, 1, 2};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

    // glGenBuffers(1, &index_buff);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buff);
    // index_buff =
    //    std::make_unique<IIndexBuffer>(IIndexBuffer::create(idx, sizeof(idx) / sizeof(uint32_t)));
    index_buff.reset(IIndexBuffer::create(idx, sizeof(idx) / sizeof(uint32_t)));

    std::string vertex_src = R"(
        #version 330 core

        layout(location = 0) in vec3 pos;

        out vec3 v_pos;

        void main() {
            v_pos = pos;
            gl_Position = vec4(pos, 1.0);
        }
    )";

    std::string frag_src = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_pos;

        void main() {
            color = vec4(v_pos * 0.5 + 0.5, 0.8);
        }
    )";

    shader = std::make_unique<Shader>(vertex_src, frag_src);
}

Application::~Application() {}

void Application::run() {

    while (running) {
        glClearColor(0.3f, 0.3f, 0.3f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        shader->bind();

        glBindVertexArray(vertex_arr);
        glDrawElements(GL_TRIANGLES, index_buff->getIndexCnt(), GL_UNSIGNED_INT, nullptr);

        for (Layer *layer : layer_list)
            layer->onUpdate();

        imgui_layer->begin();
        for (Layer *layer : layer_list)
            layer->onImGuiRender();
        imgui_layer->end();

        // CBRM_CORE_TRACE("[{0}, {0}]", Input::getMouseX(), Input::getMouseY());

        window->update();
    }
}

void Application::onEvent(Event &e) {
    // CBRM_CORE_INFO("{0}", e);

    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowCloseEvent, this, _1));

    for (auto it = layer_list.rbegin(); it != layer_list.rend(); ++it) {
        (*it)->onEvent(e);
        if (e.handled)
            break;
    }
}

void Application::pushLayer(Layer *layer) {
    layer_list.pushLayer(layer);
    layer->onAttach();
}

void Application::pushOverlay(Layer *layer) {
    layer_list.pushOverlay(layer);
    layer->onAttach();
}

bool Application::onWindowCloseEvent(WindowCloseEvent &e) {
    running = false;

    return true;
}

} // namespace cabrium