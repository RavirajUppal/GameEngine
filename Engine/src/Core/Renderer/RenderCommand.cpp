#include "RenderCommand.h"
#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace RealEngine{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}