#pragma once
#include <memory>

namespace RenderEngine {

    class IndexBuffer {
    public:
        IndexBuffer() = default;
        virtual ~IndexBuffer() = default;

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        virtual void init(const void* data, const unsigned int count) = 0;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual unsigned int getCount() const = 0;

        static std::unique_ptr<IndexBuffer> Create();
    };

}