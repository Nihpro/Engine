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

		void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
		void bind() const;
		void unbind() const;

	private:
		uint32_t m_id = 0;
		uint32_t m_elementsCount = 0;
	};
}