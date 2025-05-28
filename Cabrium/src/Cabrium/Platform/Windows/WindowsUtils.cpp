#include "cbrm_pch.h"

#include "Cabrium/Common/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace cabrium {

float Time::getTime() { return glfwGetTime(); }

} // namespace cabrium