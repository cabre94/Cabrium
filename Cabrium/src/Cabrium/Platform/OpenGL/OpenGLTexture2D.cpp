#include "cbrm_pch.h"

#include "OpenGLTexture2D.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace cabrium {

OpenGLTexture2D::OpenGLTexture2D(const std::string &path_) : path(path_) {

    int width_, height_, channel_;

    stbi_set_flip_vertically_on_load(1);

    stbi_uc *data = stbi_load(path.c_str(), &width_, &height_, &channel_, 0);

    CBRM_CORE_ASSERT(data, "OpenGLTexture2D::OpenGLTexture2D - error opening file");

    width  = width_;
    height = height_;

    glCreateTextures(GL_TEXTURE_2D, 1, &render_id);
    glTextureStorage2D(render_id, 1, GL_RGB8, width, height);

    glTextureParameteri(render_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTextureParameteri(render_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(render_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureSubImage2D(render_id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &render_id); }

void OpenGLTexture2D::bind(uint32_t slot) { glBindTextureUnit(slot, render_id); }

// void OpenGLTexture2D::unbind() { glUnbindTextureUnit(0, render_id); }

} // namespace cabrium