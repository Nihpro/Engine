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

		void init(const void* data, const unsigned int count);
		void bind() const;
		void unbind() const;
		unsigned int getCount() const { return m_count; };

	private:
		uint32_t m_id;
		uint32_t m_count;
	};
}