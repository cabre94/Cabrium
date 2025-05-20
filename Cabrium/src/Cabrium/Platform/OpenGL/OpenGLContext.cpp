#include "cbrm_pch.h"

#include "OpenGLContext.h"

#include "Cabrium/Common/Basic.h"

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
}

void OpenGLContext::swapBuffers() {
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

} // namespace cabrium