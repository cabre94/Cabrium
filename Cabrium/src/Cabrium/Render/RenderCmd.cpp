#include "cbrm_pch.h"

#include "RenderCmd.h"

#include "Cabrium/Platform/OpenGL/OpenGLRenderAPI.h"

namespace cabrium {

RenderAPI *RenderCmd::render_api = new OpenGLRenderAPI();

}