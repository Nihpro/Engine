#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <memory>

namespace RenderEngine {

    class VertexArray {
    public:
        VertexArray() = default;
        virtual ~VertexArray() = default;

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        virtual void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) = 0;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static std::unique_ptr<VertexArray> Create();
    };

}