#include "VertexBuffer.h"
#include "../Platform/OpenGL/OpenGLVertexBuffer.h"
namespace RenderEngine{

	std::unique_ptr<VertexBuffer> VertexBuffer::Create()
	{
		return std::make_unique<RenderOpenGL::OpenGLVertexBuffer>();
	}
}
