#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include <string>
#include <memory>

namespace RenderEngine {
	class RendererAPI
	{
	public:

		virtual ~RendererAPI() = default;

		virtual void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer) = 0;
		virtual void setClearColor(const float r, const float g, const float b, const float a) = 0;
		virtual void setDepthTest(const bool enable) = 0;
		virtual void clear() = 0;
		virtual void setViewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset = 0, const unsigned int bottomOffset = 0) = 0;

		virtual std::string getRendererStr() = 0;
		virtual std::string getVersionStr() = 0;

		static std::unique_ptr<RendererAPI> Create();

	};

}