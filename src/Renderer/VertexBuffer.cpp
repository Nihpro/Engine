#include "VertexBuffer.h"
#include "../Platform/OpenGL/OpenGLVertexBuffer.h"

VertexBuffer* RenderEngine::VertexBuffer::Create()
{
	return new RenderOpenGL::OpenGLVertexBuffer();
}
