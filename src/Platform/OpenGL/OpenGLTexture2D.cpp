#include "OpenGLTexture2D.h"


namespace RenderOpenGL {

    static GLenum WRAPModeInBaseType(RenderEngine::WRAPMode type) {

        switch (type)
        {
        case RenderEngine::WRAPMode::Repeat:
            return GL_REPEAT;
            break;
        case RenderEngine::WRAPMode::Mirrored_Repeat:
            return GL_MIRRORED_REPEAT;
            break;
        case RenderEngine::WRAPMode::Clam_To_Enge:
            return GL_CLAMP_TO_EDGE;
            break;
        case RenderEngine::WRAPMode::Clam_To_Border:
            return GL_CLAMP_TO_BORDER;
            break;
        }
        return 0;
    }
    static GLenum FilterInBaseType(RenderEngine::Filter type) {

        switch (type)
        {
        case RenderEngine::Filter::Nearest:
            return GL_NEAREST;
            break;
        case RenderEngine::Filter::Linear:
            return GL_LINEAR;
            break;
        }
        return 0;
    }

	RenderOpenGL::OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, uint32_t height,
        const unsigned char* data,
        const uint32_t channels,
        const RenderEngine::Filter filter,
        const RenderEngine::WRAPMode wrapMode)  
	{
        m_width = width;
        m_height = height;

        switch (channels)
        {
        case 4:
            m_mode = GL_RGBA;
            break;
        case 3:
            m_mode = GL_RGB;
            break;
        default:
            m_mode = GL_RGBA;
            break;
        }

        glGenTextures(1, &m_ID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAPModeInBaseType(wrapMode));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAPModeInBaseType(wrapMode));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterInBaseType(filter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterInBaseType(filter));
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
	}

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_ID);
    }
    void OpenGLTexture2D::bind() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }
}