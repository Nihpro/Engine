#include "Renderer.h"
#include "RendererAPI.h"

namespace RenderEngine {

    static std::unique_ptr<RendererAPI> renderAPI{ RendererAPI::Create() };

    void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader)
    {
        shader.use();
        vertexArray.bind();
        indexBuffer.bind();
        renderAPI->draw(vertexArray, indexBuffer);
    }

    void Renderer::setClearColor(const float r, const float g, const float b, const float a)
    {
        renderAPI->setClearColor(r, g, b, a);
    }

    void Renderer::setDepthTest(const bool enable)
    {
        renderAPI->setDepthTest(enable);
    }

    void Renderer::clear()
    {
        renderAPI->clear();
    }

    void Renderer::setViewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset, const unsigned int bottomOffset)
    {
        renderAPI->setViewport(width, height, leftOffset, bottomOffset);
    }

    std::string Renderer::getRendererStr()
    {
        return renderAPI->getRendererStr();
    }

    std::string Renderer::getVersionStr()
    {
        return renderAPI->getVersionStr();
    }
}