#pragma once

#include <string>

namespace cabrium {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    static Shader *create(const std::string &vertex_src, const std::string &frag_src);
};

} // namespace cabrium