#include "cbrm_pch.h"

#include "Cabrium/Common/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace cabrium {

float Time::getTime() { return (float) glfwGetTime(); }

} // namespace cabrium