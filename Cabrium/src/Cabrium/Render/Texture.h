#pragma once

#include "Cabrium/Common/Types.h"

#include <cstdint>
#include <string>

namespace cabrium {

class Texture {
public:
    virtual ~Texture() {}
    virtual uint32_t getWidth() const  = 0;
    virtual uint32_t getHeight() const = 0;

    virtual void bind(uint32_t slot = 0) = 0;
    // virtual void unbind() = 0;
};

class Texture2D : public Texture {
public:
    virtual ~Texture2D() {}

    static Ref<Texture2D> create(const std::string &path);
};

} // namespace cabrium