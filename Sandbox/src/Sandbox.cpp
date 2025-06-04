#include <Cabrium.h>

#include "Cabrium/Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// #define CAMERA_RIGHT 1.6f
#define CAMERA_RIGHT        4.0f
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
        cabrium::Ref<cabrium::IVertexBuffer> vertex_buff(
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
            uniform mat4 transform;

            out vec3 v_pos;
            out vec4 v_color;

            void main() {
                v_pos = pos;
                v_color = color;
                gl_Position = view_proj * transform * vec4(pos, 1.0);
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

        // shader = std::make_unique<cabrium::Shader>(cabrium::Shader::create(vertex_src,
        // frag_src));
        shader.reset(cabrium::Shader::create(vertex_src, frag_src));

        // -------------------------------------------------------
        // ----------------- Square Vertex Array -----------------
        // -------------------------------------------------------
        float square_vertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // first 3 vertices
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, //
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, //
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, //
        };

        square_va = std::unique_ptr<cabrium::IVertexArray>(cabrium::IVertexArray::create());
        cabrium::Ref<cabrium::IVertexBuffer> square_vb(
            cabrium::IVertexBuffer::create(square_vertices, sizeof(square_vertices)));

        cabrium::BufferLayout square_layout = {{cabrium::ShaderDataType::Vec3, "a_Position"},
                                               {cabrium::ShaderDataType::Vec2, "a_TexCoord"}};

        square_vb->setLayout(square_layout);

        square_va->addBuffer(square_vb); // Layout has to be set before!

        // index buffer
        // uint32_t square_idx[4] = {0, 1, 2, 3};
        uint32_t square_idx[6] = {0, 1, 2, 2, 3, 0};

        cabrium::Ref<cabrium::IIndexBuffer> square_ib(
            cabrium::IIndexBuffer::create(square_idx, sizeof(square_idx) / sizeof(uint32_t)));
        square_ib->bind();
        square_va->setIndexBuffer(square_ib);

        std::string vertex_src_square = R"(
            #version 330 core

            layout(location = 0) in vec3 pos;

            uniform mat4 view_proj;
            uniform mat4 transform;

            out vec3 v_pos;

            void main() {
                v_pos = pos;
                gl_Position = view_proj * transform * vec4(pos, 1.0);
            }
        )";

        std::string frag_src_square = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec3 u_color;
            in vec3 v_pos;

            void main() {
                color = vec4(u_color, 1.0);
            }
        )";

        std::string vertex_src_texture = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 view_proj;
            uniform mat4 transform;

            out vec2 v_TexCoord;

            void main() {
                v_TexCoord = a_TexCoord;
                gl_Position = view_proj * transform * vec4(a_Position, 1.0);
            }
        )";

        std::string frag_src_texture = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

            void main() {
                color = texture(u_Texture, v_TexCoord);
            }
        )";

        square_shader.reset(cabrium::Shader::create(vertex_src_square, frag_src_square));

        texture_shader.reset(cabrium::Shader::create(vertex_src_texture, frag_src_texture));
        texture = cabrium::Texture2D::create("assets/textures/Checkerboard.png");

        texture_shader->bind();

        std::dynamic_pointer_cast<cabrium::OpenGLShader>(texture_shader)
            ->setUnirform1i("u_Texture", 0); // texture slot = 0
    }

    void onUpdate(cabrium::DeltaTime dt) override {

        // CBRM_INFO("dt = {0}s - {1}ms", dt.getSeconds(), dt.getMilliSeconds());

        // Camera
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

        // Square
        if (cabrium::Input::isKeyPressed(cabrium::key::J))
            square_pos.x -= square_move_speed * dt;
        else if (cabrium::Input::isKeyPressed(cabrium::key::L))
            square_pos.x += square_move_speed * dt.getSeconds();

        if (cabrium::Input::isKeyPressed(cabrium::key::I))
            square_pos.y += square_move_speed * dt;
        else if (cabrium::Input::isKeyPressed(cabrium::key::K))
            square_pos.y -= square_move_speed * dt;

        // static float t = 0;
        // t += 5e-2f;
        cabrium::RenderCmd::setClearColor({0.3f, 0.3f, 0.3f, 1});
        cabrium::RenderCmd::clear();

        // camera.setPosition({std::cos(t), std::sin(t * 0.7), 0.0f});
        // camera.setRotation(t * 100);
        camera.setPosition(camera_pos);
        camera.setRotation(camera_rotation);

        cabrium::Renderer::beginScene(camera); // Renderer::beginScene(camera, lights, enviroments);

        // bind shaders
        // std::dynamic_pointer_cast<cabrium::OpenGLShader>(shader)->bind();
        // std::dynamic_pointer_cast<cabrium::OpenGLShader>(square_shader)->bind();
        shader->bind();
        square_shader->bind();

        std::dynamic_pointer_cast<cabrium::OpenGLShader>(square_shader)
            ->setUnirform3f("u_color", square_color);

        // glm::mat4 transform = glm::translate(glm::mat4(1.0f), square_pos);
        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        glm::vec4 square_color = glm::vec4(16.0f, 63.0f, 121.0f, 1.0f) / 255.0f;
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos + square_pos) * scale;
                cabrium::Renderer::submit(square_shader, square_va, transform);
            }
        }

        texture->bind();
        cabrium::Renderer::submit(texture_shader, square_va,
                                  glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

        // Triangle
        // cabrium::Renderer::submit(shader, vertex_arr);

        cabrium::Renderer::endScene();
    }

    bool onKeyPressedEvent(cabrium::KeyPressedEvent &e) { return false; }

    bool onMouseScrolled(cabrium::MouseScrolledEvent &e) {

        // if (cabrium::Input::isKeyPressed(cabrium::key::Up))
        //     camera_pos.y += camera_move_speed * dt;
        // else if (cabrium::Input::isKeyPressed(cabrium::key::Down))
        //     camera_pos.y -= camera_move_speed * dt;

        camera_pos.z += e.getOffsetY();

        return false;
    }

    void onEvent(cabrium::Event &e) override {
        // CBRM_TRACE("DummyLayer::onEvent - event {0}", e);

        cabrium::EventDispatcher dispatcher(e);
        dispatcher.dispatch<cabrium::MouseScrolledEvent>(
            std::bind(&DummyLayer::onMouseScrolled, this, _1));
    }

    void onImGuiRender() override {
        ImGui::Begin("Coso");

        ImGui::Text("Hello Coso");
        ImGui::ColorEdit3("SquareColor", glm::value_ptr(square_color));

        ImGui::End();
    }

private:
    cabrium::Ref<cabrium::Shader> shader;
    cabrium::Ref<cabrium::IVertexArray> vertex_arr;

    cabrium::Ref<cabrium::Shader> square_shader, texture_shader;
    cabrium::Ref<cabrium::IVertexArray> square_va;

    cabrium::Ref<cabrium::Texture> texture;

    cabrium::OrthographicCamera camera;

    glm::vec4 camera_pos;
    float camera_move_speed = 5.0f; // per second
    float square_move_speed = 5.0f; // per second

    float camera_rotation       = 0;
    float camera_rotation_speed = 90.0f; // degrees per second

    glm::vec3 square_pos{0.0f};
    glm::vec3 square_color = glm::vec3(16.0f, 63.0f, 121.0f) / 255.0f;
};

class Sandbox : public cabrium::Application {
public:
    Sandbox() : Application() {
        pushLayer(new DummyLayer());
        // pushLayer(new cabrium::ImGuiLayer());
    }
    ~Sandbox() {}
};

cabrium::Application *cabrium::createApplication() { return new Sandbox(); }
