#pragma once
#include <vector>
#include <stdint.h>

namespace RenderEngine {

    enum class DataType {
        Float,
        Int
    };

    struct VertexBufferLayoutElement {
        int count;
        DataType type;
        unsigned char normalized;
        unsigned int size;
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout();

        void reserveElements(const size_t count);
        unsigned int getStride() const { return m_stride; }
        void addElementLayoutFloat(const unsigned int count, const bool normalized);
        const std::vector<VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElments; }

    private:
        std::vector<VertexBufferLayoutElement> m_layoutElments;
        unsigned int m_stride;
    };

}