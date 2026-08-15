#pragma once
#include "../../Renderer/IndexBuffer.h"
#include <stdint.h>

using namespace RenderEngine;

namespace RenderOpenGL {
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer() override;

		void init(const void* data, const unsigned int count) override;
		void bind() const override;
		void unbind() const override;
		unsigned int getCount() const override { return m_count; } ;

	private:
		uint32_t m_id;
		uint32_t m_count;
	};
}