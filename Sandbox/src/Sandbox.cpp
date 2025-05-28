#include <Cabrium.h>

#include "imgui.h"

#define CAMERA_RIGHT        5.0f
#define CAMERA_LEFT         (-1 * CAMERA_RIGHT)
#define CAMERA_SCALE_FACTOR 0.5625f
#define CAMERA_BOTTOM       (CAMERA_LEFT * CAMERA_SCALE_FACTOR)
#define CAMERA_TOP          (CAMERA_RIGHT * CAMERA_SCALE_FACTOR)

using namespace std::placeholders;

class DummyLayer : public cabrium::Layer {
public:
    DummyLayer()
        : Layer("DummyLayer"),
          camera(CAMERA_LEFT, CAMERA_RIGHT, CAMERA_BOTTOM, CAMERA_TOP),
          camera_pos{} {
        camera.setPosition(camera_pos);

        // Vertex array
        vertex_arr = std::unique_ptr<cabrium::IVertexArray>(cabrium::IVertexArray::create());
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
        std::shared_ptr<cabrium::IVertexBuffer> vertex_buff(
            cabrium::IVertexBuffer::create(vertices, sizeof(vertices)));
        vertex_buff->bind();

        cabrium::BufferLayout layout = {{cabrium::ShaderDataType::Vec3, "a_Position"},
                                        {cabrium::ShaderDataType::Vec4, "a_Color"}};

        vertex_buff->setLayout(layout);

        // Layout has to be set before!
        vertex_arr->addBuffer(vertex_buff);

        // index buffer
        uint32_t idx[3] = {0, 1, 2};
        std::shared_ptr<cabrium::IIndexBuffer> index_buff(
            cabrium::IIndexBuffer::create(idx, sizeof(idx) / sizeof(uint32_t)));
        index_buff->bind();

        vertex_arr->setIndexBuffer(index_buff);

        std::string vertex_src = R"(
            #version 330 core

            layout(location = 0) in vec3 pos;
            layout(location = 1) in vec4 color;

            uniform mat4 view_proj;

            out vec3 v_pos;
            out vec4 v_color;

            void main() {
                v_pos = pos;
                v_color = color;
                gl_Position = view_proj * vec4(pos, 1.0);
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

        shader = std::make_unique<cabrium::Shader>(vertex_src, frag_src);
        // -------------------------------------------------------
        // ----------------- Square Vertex Array -----------------
        // -------------------------------------------------------
        float square_vertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f, // first 3 vertices
            0.75f,  -0.75f, 0.0f, //
            0.75f,  0.75f,  0.0f, //
            -0.75f, 0.75f,  0.0f, //
        };

        square_va = std::unique_ptr<cabrium::IVertexArray>(cabrium::IVertexArray::create());
        std::shared_ptr<cabrium::IVertexBuffer> square_vb(
            cabrium::IVertexBuffer::create(square_vertices, sizeof(square_vertices)));

        cabrium::BufferLayout square_layout = {{cabrium::ShaderDataType::Vec3, "a_Position"}};

        square_vb->setLayout(square_layout);

        square_va->addBuffer(square_vb); // Layout has to be set before!

        // index buffer
        // uint32_t square_idx[4] = {0, 1, 2, 3};
        uint32_t square_idx[6] = {0, 1, 2, 2, 3, 0};

        std::shared_ptr<cabrium::IIndexBuffer> square_ib(
            cabrium::IIndexBuffer::create(square_idx, sizeof(square_idx) / sizeof(uint32_t)));
        square_ib->bind();
        square_va->setIndexBuffer(square_ib);

        std::string vertex_src_square = R"(
        #version 330 core

        layout(location = 0) in vec3 pos;

        uniform mat4 view_proj;

        out vec3 v_pos;

        void main() {
            v_pos = pos;
            gl_Position = view_proj * vec4(pos, 1.0);
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

        square_shader = std::make_unique<cabrium::Shader>(vertex_src_square, frag_src_square);
    }

    void onUpdate(cabrium::DeltaTime dt) override {

        // CBRM_INFO("dt = {0}s - {1}ms", dt.getSeconds(), dt.getMilliSeconds());

        if (cabrium::Input::isKeyPressed(cabrium::key::Left))
            camera_pos.x -= camera_move_speed * dt;
        else if (cabrium::Input::isKeyPressed(cabrium::key::Right))
            camera_pos.x += camera_move_speed * dt.getSeconds();

        if (cabrium::Input::isKeyPressed(cabrium::key::Up))
            camera_pos.y += camera_move_speed * dt;
        else if (cabrium::Input::isKeyPressed(cabrium::key::Down))
            camera_pos.y -= camera_move_speed * dt;

        if (cabrium::Input::isKeyPressed(cabrium::key::A))
            camera_rotation += camera_rotation_speed * dt;
        else if (cabrium::Input::isKeyPressed(cabrium::key::D))
            camera_rotation -= camera_rotation_speed * dt;

        // static float t = 0;
        // t += 5e-2f;
        cabrium::RenderCmd::setClearColor({0.3f, 0.3f, 0.3f, 1});
        cabrium::RenderCmd::clear();

        // camera.setPosition({std::cos(t), std::sin(t * 0.7), 0.0f});
        // camera.setRotation(t * 100);
        camera.setPosition(camera_pos);
        camera.setRotation(camera_rotation);

        cabrium::Renderer::beginScene(camera); // Renderer::beginScene(camera, lights, enviroments);

        cabrium::Renderer::submit(square_shader, square_va);
        cabrium::Renderer::submit(shader, vertex_arr);

        cabrium::Renderer::endScene();
    }

    bool onKeyPressedEvent(cabrium::KeyPressedEvent &e) {

        // CBRM_INFO("onKeyPressedEvent - {0} ", e);

        // if (e.getKeyCode() == cabrium::key::Left) {
        //     camera_pos.x -= camera_move_speed;
        // }

        // switch (e.getKeyCode()) {
        //     case cabrium::key::Left: camera_pos.x -= camera_move_speed; break;
        //     case cabrium::key::Right: camera_pos.x += camera_move_speed; break;
        //     case cabrium::key::Up: camera_pos.y += camera_move_speed; break;
        //     case cabrium::key::Down: camera_pos.y -= camera_move_speed; break;
        //     case cabrium::key::A: camera_rotation -= camera_move_speed; break;
        //     case cabrium::key::D: camera_rotation += camera_move_speed; break;
        //     default: break;
        // }
        // return false;
    }

    void onEvent(cabrium::Event &e) override {
        // CBRM_TRACE("DummyLayer::onEvent - event {0}", e);

        // cabrium::EventDispatcher dispatcher(e);

        // dispatcher.dispatch<cabrium::KeyPressedEvent>(
        //     std::bind(&DummyLayer::onKeyPressedEvent, this, _1));
    }

    void onImGuiRender() override {
        // ImGui::Begin("DummyLayer");
        // ImGui::Text("Hello DummyLayer");
        // ImGui::End();
    }

private:
    std::shared_ptr<cabrium::Shader> shader;
    std::shared_ptr<cabrium::IVertexArray> vertex_arr;

    std::shared_ptr<cabrium::Shader> square_shader;
    std::shared_ptr<cabrium::IVertexArray> square_va;

    cabrium::OrthographicCamera camera;

    glm::vec4 camera_pos;
    float camera_move_speed = 5.0f; // per second

    float camera_rotation       = 0;
    float camera_rotation_speed = 90.0f; // degrees per second
};

class Sandbox : public cabrium::Application {
public:
    Sandbox() : Application() {
        pushLayer(new DummyLayer());
        // pushLayer(new cabrium::ImGuiLayer());
    }
    ~Sandbox() {}
};

cabrium::Application *cabrium::createApplication() {
    //
    return new Sandbox();
}
