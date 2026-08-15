#include "VertexArray.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace RenderEngine {
	std::unique_ptr<VertexArray> VertexArray::Create()
	{
		return std::make_unique<RenderOpenGL::OpenGLVertexArray>();
	}
}