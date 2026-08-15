#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace RenderOpenGL {
    OpenGLIndexBuffer::OpenGLIndexBuffer()
        : m_id(0)
        , m_count(0)
    {}

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLIndexBuffer::init(const void* data, const unsigned int count)
    {
        m_count = count;
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    }

    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}