#pragma once

#include <cstdint>
#include <string>

namespace cabrium {

class Shader {
public:
    Shader(const std::string &vertex_src, const std::string &frag_src);
    ~Shader();

    void bind() const;
    void unbind() const;

private:
    uint32_t render_id;
};

} // namespace cabrium