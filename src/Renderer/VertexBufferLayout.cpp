#include "VertexBufferLayout.h"

namespace RenderEngine {
    VertexBufferLayout::VertexBufferLayout()
        : m_stride(0)
    {}

    void VertexBufferLayout::reserveElements(const size_t count)
    {
        m_layoutElments.reserve(count);
    }

    void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
    {
        m_layoutElments.push_back({ static_cast<int>(count), DataType::Float, normalized, count * static_cast<uint32_t>(sizeof(float)) });
        m_stride += m_layoutElments.back().size;
    }

}