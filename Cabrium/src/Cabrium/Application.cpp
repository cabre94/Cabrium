#include "cbrm_pch.h"

#include "Application.h"

#include "Cabrium/Common/Input.h"
#include "Cabrium/Common/Log.h"
#include "Cabrium/Common/Window.h"
#include "Cabrium/Events/EventDispatcher.h"

// Remove
#include "Cabrium/Render/BufferLayout.h"
#include "Cabrium/Render/Buffers.h"
#include "Cabrium/Render/Shader.h"
#include "Cabrium/Render/VertexArray.h"

#include <glad/glad.h>

using namespace std::placeholders;

namespace cabrium {

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
    vertex_arr = std::unique_ptr<IVertexArray>(IVertexArray::create());
    vertex_arr->bind();

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f,       // first 3 vertices
        0.0f,  1.0f,  1.0f, 1.0f, // first color components

        0.5f,  -0.5f, 0.0f,       //
        1.0f,  0.0f,  1.0f, 1.0f, //  2nd color components

        0.0f,  0.5f,  0.0f,      //
        1.0f,  1.0f,  0.0f, 1.0f //  3th color components
    };

    // Vertex buffer
    std::shared_ptr<IVertexBuffer> vertex_buff(IVertexBuffer::create(vertices, sizeof(vertices)));
    vertex_buff->bind();

    BufferLayout layout = {{ShaderDataType::Vec3, "a_Position"}, {ShaderDataType::Vec4, "a_Color"}};

    vertex_buff->setLayout(layout);

    // Layout has to be set before!
    vertex_arr->addBuffer(vertex_buff);

    // index buffer
    uint32_t idx[3] = {0, 1, 2};
    std::shared_ptr<IIndexBuffer> index_buff(
        IIndexBuffer::create(idx, sizeof(idx) / sizeof(uint32_t)));
    index_buff->bind();

    vertex_arr->setIndexBuffer(index_buff);

    std::string vertex_src = R"(
        #version 330 core

        layout(location = 0) in vec3 pos;
        layout(location = 1) in vec4 color;

        out vec3 v_pos;
        out vec4 v_color;

        void main() {
            v_pos = pos;
            v_color = color;
            gl_Position = vec4(pos, 1.0);
        }
    )";

    std::string frag_src = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_pos;
        in vec4 v_color;

        void main() {
            color = vec4(v_pos * 0.5 + 0.5, 0.8);
            color = v_color;
        }
    )";

    shader = std::make_unique<Shader>(vertex_src, frag_src);
    // -------------------------------------------------------
    // ----------------- Square Vertex Array -----------------
    // -------------------------------------------------------
    float square_vertices[3 * 4] = {
        -0.5f, -0.5f, 0.0f, // first 3 vertices
        0.5f,  -0.5f, 0.0f, //
        0.5f,  0.5f,  0.0f, //
        -0.5f, 0.5f,  0.0f, //
    };

    square_va = std::unique_ptr<IVertexArray>(IVertexArray::create());
    std::shared_ptr<IVertexBuffer> square_vb(
        IVertexBuffer::create(square_vertices, sizeof(square_vertices)));

    BufferLayout square_layout = {{ShaderDataType::Vec3, "a_Position"}};

    square_vb->setLayout(square_layout);

    square_va->addBuffer(square_vb); // Layout has to be set before!

    // index buffer
    // uint32_t square_idx[4] = {0, 1, 2, 3};
    uint32_t square_idx[6] = {0, 1, 2, 2, 3, 0};

    std::shared_ptr<IIndexBuffer> square_ib(
        IIndexBuffer::create(square_idx, sizeof(square_idx) / sizeof(uint32_t)));
    square_ib->bind();
    square_va->setIndexBuffer(square_ib);

    std::string vertex_src_square = R"(
        #version 330 core

        layout(location = 0) in vec3 pos;

        out vec3 v_pos;

        void main() {
            v_pos = pos;
            gl_Position = vec4(pos, 1.0);
        }
    )";

    std::string frag_src_square = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_pos;

        void main() {
            color = vec4(0.2f, 0.3f, 0.9f, 0.8);
        }
    )";

    square_shader = std::make_unique<Shader>(vertex_src_square, frag_src_square);
}

Application::~Application() {}

void Application::run() {

    while (running) {
        glClearColor(0.3f, 0.3f, 0.3f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        square_shader->bind();
        square_va->bind();
        glDrawElements(GL_TRIANGLES, square_va->getIndexBuffer()->getIndexCnt(), GL_UNSIGNED_INT,
                       nullptr);

        shader->bind();
        vertex_arr->bind();
        glDrawElements(GL_TRIANGLES, vertex_arr->getIndexBuffer()->getIndexCnt(), GL_UNSIGNED_INT,
                       nullptr);

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