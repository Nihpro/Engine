#pragma once
#include "../../Renderer/Texture2D.h"
#include <glad/glad.h>

namespace RenderOpenGL {
	class OpenGLTexture2D : public RenderEngine::Texture2D
	{
	public:
		OpenGLTexture2D(const uint32_t width, uint32_t height,
			const unsigned char* data,
			const uint32_t channels,
			const RenderEngine::Filter filter,
			const RenderEngine::WRAPMode wrapMode);
		~OpenGLTexture2D() override;
		void bind() const override;

	private:
		uint32_t m_ID;
		GLenum m_mode;
	};
}