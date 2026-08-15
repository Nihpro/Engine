#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace RenderOpenGL {

    static GLenum DataTypeInBaseType(RenderEngine::DataType type) {

        switch (type)
        {
        case RenderEngine::DataType::Float:
            return GL_FLOAT;
            break;
        case RenderEngine::DataType::Int:
            return GL_INT;
            break;
        }
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(m_id);
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
    {
        bind();
        vertexBuffer.bind();
        const auto& layoutElements = layout.getLayoutElements();
        GLbyte* offset = nullptr;
        for (unsigned int i = 0; i < layoutElements.size(); ++i)
        {
            const auto& currentLayoutElement = layoutElements[i];
            GLuint currentAttribIndex = m_elementsCount + i;
            glEnableVertexAttribArray(currentAttribIndex);
            glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count,DataTypeInBaseType(currentLayoutElement.type), currentLayoutElement.normalized, layout.getStride(), offset);
            offset += currentLayoutElement.size;
        }
        m_elementsCount += static_cast<unsigned int>(layoutElements.size());
    }
}

