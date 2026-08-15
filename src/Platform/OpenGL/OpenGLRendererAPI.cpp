#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace RenderOpenGL {
	void OpenGLRendererAPI::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer)
	{
		glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRendererAPI::setClearColor(const float r, const float g, const float b, const float a)
	{
		glClearColor(r, g, b, a);
	}
	void OpenGLRendererAPI::setDepthTest(const bool enable)
	{
		if (enable)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}
	void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::setViewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset, const unsigned int bottomOffset)
	{
		glViewport(leftOffset, bottomOffset, width, height);
	}
	std::string OpenGLRendererAPI::getRendererStr()
	{
		return (const char*)glGetString(GL_RENDERER);
	}
	std::string OpenGLRendererAPI::getVersionStr()
	{
		return (const char*)glGetString(GL_VERSION);
	}
}