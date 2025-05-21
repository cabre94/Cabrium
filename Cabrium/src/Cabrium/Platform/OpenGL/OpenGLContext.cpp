#include "cbrm_pch.h"

#include "OpenGLContext.h"

#include "Cabrium/Common/Basic.h"
#include "Cabrium/Common/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace cabrium {

//

OpenGLContext::OpenGLContext(GLFWwindow *window_) : window(window_) {
    CBRM_CORE_ASSERT(window, "OpenGLContext::OpenGLContext - window not initialized");
}

void OpenGLContext::init() {

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Glad initialization
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    CBRM_CORE_ASSERT(status, "Glad initialization failed");

    CBRM_CORE_INFO("glGetString(GL_VENDOR) = {0} - {1}", (const char *) glGetString(GL_VENDOR),
                   (const char *) glGetString(GL_RENDERER));

    CBRM_CORE_INFO("OpenGL information");
    CBRM_CORE_INFO("Vendor: {0}", (const char *) glGetString(GL_VENDOR));
    CBRM_CORE_INFO("Renderer: {0}", (const char *) glGetString(GL_RENDERER));
    CBRM_CORE_INFO("Version: {0}", (const char *) glGetString(GL_VERSION));
}

void OpenGLContext::swapBuffers() {
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

} // namespace cabrium