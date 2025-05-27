#pragma once

#include <cstdint>
#include <string>

#include <glm/glm.hpp>

namespace cabrium {

class Shader {
public:
    Shader(const std::string &vertex_src, const std::string &frag_src);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUnirformMatrix4f(const std::string &name, const glm::mat4 &mat4);

private:
    int32_t getUniformLocation(const std::string &name);

    uint32_t render_id;

    std::unordered_map<std::string, int32_t> uniform_loc_cache;
};

} // namespace cabrium