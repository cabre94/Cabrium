#pragma once

#include "Cabrium/Render/Texture.h"

namespace cabrium {

class OpenGLTexture2D : public Texture2D {

public:
    OpenGLTexture2D(const std::string &path_);
    virtual ~OpenGLTexture2D();

    uint32_t getWidth() const override { return width; }
    uint32_t getHeight() const override { return height; }

    void bind(uint32_t slot = 0) override;
    // void unbind() override;

private:
    std::string path;
    uint32_t width, height;

    uint32_t render_id;
};

} // namespace cabrium