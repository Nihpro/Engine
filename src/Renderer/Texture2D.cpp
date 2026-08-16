#include "Texture2D.h"
#include "../Platform/OpenGL/OpenGLTexture2D.h"

namespace RenderEngine {

    

    std::unique_ptr<Texture2D> Texture2D::Create(const uint32_t width, uint32_t height,
        const unsigned char* data,
        const uint32_t channels,
        const Filter filter,
        const WRAPMode wrapMode)
    {
        return std::make_unique<RenderOpenGL::OpenGLTexture2D>(width,height, data, channels, filter, wrapMode);
    }

    void Texture2D::addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV)
    {
        m_subTextures.emplace(std::move(name), SubTexture2D(leftBottomUV, rightTopUV));
    }

    const Texture2D::SubTexture2D& Texture2D::getSubTexture(const std::string& name) const
    {
        auto it = m_subTextures.find(name);
        if (it != m_subTextures.end())
        {
            return it->second;
        }
        const static SubTexture2D defaultSubTexture;
        return defaultSubTexture;
    }
}