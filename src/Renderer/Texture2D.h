#pragma once
#include <glm/vec2.hpp>
#include <string>
#include <map>
#include <memory>

namespace RenderEngine {

    enum class WRAPMode {
        Repeat,
        Mirrored_Repeat,
        Clam_To_Enge,
        Clam_To_Border
    };

    enum class Filter {
        Nearest,
        Linear
    };


    class Texture2D
    {
    public:


        struct SubTexture2D
        {
            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;

            SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV)
                : leftBottomUV(_leftBottomUV)
                , rightTopUV(_rightTopUV)
            {}

            SubTexture2D()
                : leftBottomUV(0.f)
                , rightTopUV(1.f)
            {}
        };

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
        

        void addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
        const SubTexture2D& getSubTexture(const std::string& name) const;
        uint32_t width() const { return m_width; }
        uint32_t height() const { return m_height; }

        Texture2D() = default;
        virtual ~Texture2D() = default;
        virtual void bind() const = 0;

        static std::unique_ptr<Texture2D> Create(const uint32_t width, uint32_t height,
            const unsigned char* data,
            const uint32_t channels = 4,
            const Filter filter = Filter::Linear,
            const WRAPMode wrapMode = WRAPMode::Clam_To_Enge);

    protected:
        uint32_t m_width;
        uint32_t m_height;

        std::map<std::string, SubTexture2D> m_subTextures;
    };
}