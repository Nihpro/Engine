#pragma once
#include "../../Renderer/RendererAPI.h"

using namespace RenderEngine;
namespace RenderOpenGL {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		// Унаследовано через RendererAPI
		void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer) override;
		void setClearColor(const float r, const float g, const float b, const float a) override;
		void setDepthTest(const bool enable) override;
		void clear() override;
		void setViewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset, const unsigned int bottomOffset) override;
		std::string getRendererStr() override;
		std::string getVersionStr() override;

	};
}
