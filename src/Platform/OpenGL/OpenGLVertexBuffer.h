#pragma once
#include "../../Renderer/VertexBuffer.h"
#include <stdint.h>

using namespace RenderEngine;

namespace RenderOpenGL {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer() override;

		// Унаследовано через VertexBuffer
		void init(const void* data, const unsigned int size) override;
		void update(const void* data, const unsigned int size) const override;
		void bind() const override;
		void unbind() const override;

	private:
		uint32_t m_id;
	};
}