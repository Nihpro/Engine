#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>


    class Texture2D;
    class Shader;

    class Sprite {
    public:
        struct FrameDescription {
            FrameDescription(const glm::vec2& lb, const glm::vec2& rt, double dur)
                : leftBottomUV(lb), rightTopUV(rt), duration(dur) {}
            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;
            double duration;
        };

        // Обновленный конструктор
        Sprite(std::shared_ptr<Texture2D> pTexture,
            std::string initialSubTexture,
            std::shared_ptr<Shader> pShaderProgram);

        void setTexture(std::shared_ptr<Texture2D> texture) { m_pTexture = texture; }
        std::shared_ptr<Texture2D> getTexture() const { return m_pTexture; }

        void setColor(const glm::vec3& color) { m_color = color; }
        const glm::vec3& getColor() const { return m_color; }

        void setSize(const glm::vec2& size) { m_size = size; }
        const glm::vec2& getSize() const { return m_size; }

        // Работа с анимацией
        void insertFrames(std::vector<FrameDescription> framesDescriptions);

        // Ваша логика с координатами (доработанная)
        void setTextureRect(const glm::vec2& min, const glm::vec2& max);
        void getTextureCoords(glm::vec2 coords[4]) const;

    private:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<Shader> m_pShaderProgram;
        std::string m_initialSubTexture;
        std::vector<FrameDescription> m_frames;

        glm::vec3 m_color = glm::vec3(1.0f);
        glm::vec2 m_size = glm::vec2(100.0f, 100.0f);
        glm::vec2 m_texCoordMin = glm::vec2(0.0f, 0.0f);
        glm::vec2 m_texCoordMax = glm::vec2(1.0f, 1.0f);
    };
