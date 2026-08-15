#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLRendererAPI.h"

namespace RenderEngine
{
    std::unique_ptr<RendererAPI> RendererAPI::Create()
    {
        return std::make_unique<RenderOpenGL::OpenGLRendererAPI>();
    }
}
