#pragma once

#include "Cabrium/Render/Shader.h"

#include <cstdint>
#include <string>

#include <glm/glm.hpp>

namespace cabrium {

class OpenGLShader : public Shader {
public:
    OpenGLShader(const std::string &vertex_src, const std::string &frag_src);
    virtual ~OpenGLShader();

    void bind() const override;
    void unbind() const override;

    void setUnirform1i(const std::string &name, int val);

    void setUnirform1f(const std::string &name, float val);
    void setUnirform2f(const std::string &name, const glm::vec2 &vec2);
    void setUnirform3f(const std::string &name, const glm::vec3 &vec3);
    void setUnirform4f(const std::string &name, const glm::vec4 &vec4);

    void setUnirformMatrix3f(const std::string &name, const glm::mat3 &mat3);
    void setUnirformMatrix4f(const std::string &name, const glm::mat4 &mat4);

private:
    int32_t getUniformLocation(const std::string &name);

    uint32_t render_id;

    std::unordered_map<std::string, int32_t> uniform_loc_cache;
};

} // namespace cabrium