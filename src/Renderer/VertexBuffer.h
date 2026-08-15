#pragma once

#include <memory>

namespace RenderEngine {

    class VertexBuffer {
    public:
        
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        virtual void init(const void* data, const unsigned int size) = 0;
        virtual void update(const void* data, const unsigned int size) const = 0;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;        

        static std::unique_ptr<VertexBuffer> Create();
    };

}