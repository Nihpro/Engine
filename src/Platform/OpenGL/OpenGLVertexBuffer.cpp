#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace RenderOpenGL {
    OpenGLVertexBuffer::OpenGLVertexBuffer()
        : m_id(0)
    {}

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLVertexBuffer::init(const void* data, const unsigned int size)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void OpenGLVertexBuffer::update(const void* data, const unsigned int size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}



