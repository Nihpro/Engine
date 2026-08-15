#pragma once
#include "../../Renderer/VertexArray.h"
#include <stdint.h>

using namespace RenderEngine;

namespace RenderOpenGL {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) override;
		void bind() const override;
		void unbind() const override;

	private:
		uint32_t m_id = 0;
		uint32_t m_elementsCount = 0;
	};
}