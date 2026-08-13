#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

RenderOpenGL::OpenGLVertexBuffer::OpenGLVertexBuffer() 
    : m_id(0)
{}

RenderOpenGL::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void RenderOpenGL::OpenGLVertexBuffer::init(const void* data, const unsigned int size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void RenderOpenGL::OpenGLVertexBuffer::update(const void* data, const unsigned int size) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void RenderOpenGL::OpenGLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void RenderOpenGL::OpenGLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

