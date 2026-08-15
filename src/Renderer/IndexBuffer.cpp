#include "IndexBuffer.h"
#include "../Platform/OpenGL/OpenGLIndexBuffer.h"

namespace RenderEngine {
	std::unique_ptr<IndexBuffer> IndexBuffer::Create()
	{
		return std::make_unique<RenderOpenGL::OpenGLIndexBuffer>();
	}
}