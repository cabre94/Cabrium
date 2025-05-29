#include "cbrm_pch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace cabrium {

OpenGLShader::OpenGLShader(const std::string &vertex_src, const std::string &frag_src)
    : /*Shader(vertex_src, frag_src),*/ render_id(0) {

    // Create an empty vertex shader handle
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *) vertex_src.c_str();
    glShaderSource(vertex_shader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertex_shader);

    GLint compiled_ok = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compiled_ok);
    if (compiled_ok == GL_FALSE) {
        GLint max_len = 0;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_len);

        // The max_len includes the NULL character
        std::vector<GLchar> infoLog(max_len);
        glGetShaderInfoLog(vertex_shader, max_len, &max_len, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertex_shader);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        return;
    }

    // Create an empty fragment shader handle
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *) frag_src.c_str();
    glShaderSource(fragment_shader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled_ok);
    if (compiled_ok == GL_FALSE) {
        GLint max_len = 0;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_len);

        // The max_len includes the NULL character
        std::vector<GLchar> infoLog(max_len);
        glGetShaderInfoLog(fragment_shader, max_len, &max_len, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragment_shader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertex_shader);

        // Use the infoLog as you see fit.
        CBRM_CORE_ERROR("{0}", infoLog.data());
        CBRM_CORE_ASSERT(0, "Fragment shader compilation fail");
        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    render_id = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(render_id, vertex_shader);
    glAttachShader(render_id, fragment_shader);

    // Link our program
    glLinkProgram(render_id);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(render_id, GL_LINK_STATUS, (int *) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(render_id, GL_INFO_LOG_LENGTH, &maxLength);

        // The max_len includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(render_id, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(render_id);
        // Don't leak shaders either.
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        // Use the infoLog as you see fit.
        CBRM_CORE_ERROR("{0}", infoLog.data());
        CBRM_CORE_ASSERT(0, "Shader link compilation fail");
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(render_id, vertex_shader);
    glDetachShader(render_id, fragment_shader);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(render_id); }

void OpenGLShader::bind() const { glUseProgram(render_id); }

void OpenGLShader::unbind() const { glUseProgram(0); }

void OpenGLShader::setUnirform1i(const std::string &name, int val) {
    glUniform1i(getUniformLocation(name), val);
}

void OpenGLShader::setUnirform1f(const std::string &name, float val) {
    glUniform1f(getUniformLocation(name), val);
}

void OpenGLShader::setUnirform2f(const std::string &name, const glm::vec2 &vec2) {
    glUniform2f(getUniformLocation(name), vec2.x, vec2.y);
}

void OpenGLShader::setUnirform3f(const std::string &name, const glm::vec3 &vec3) {
    glUniform3f(getUniformLocation(name), vec3.x, vec3.y, vec3.z);
}

// Set uniforms assume shader already bind
void OpenGLShader::setUnirform4f(const std::string &name, const glm::vec4 &vec4) {
    glUniform4f(getUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void OpenGLShader::setUnirformMatrix3f(const std::string &name, const glm::mat3 &mat3) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat3));
}

void OpenGLShader::setUnirformMatrix4f(const std::string &name, const glm::mat4 &mat4) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat4));
}

int32_t OpenGLShader::getUniformLocation(const std::string &name) {

    if (uniform_loc_cache.find(name) != uniform_loc_cache.end())
        return uniform_loc_cache[name];

    int32_t location = glGetUniformLocation(render_id, name.c_str());
    if (location == -1) {
        std::cout << "Shader::getUniformLocation uniform " << name << " doesn't exist\n";
    }
    uniform_loc_cache[name] = location;

    return location;
}

} // namespace cabrium
