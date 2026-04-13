#include "Sprite.h"
#include "Texture2D.h"
#include "Shader.h"


    Sprite::Sprite(std::shared_ptr<Texture2D> pTexture,
        std::string initialSubTexture,
        std::shared_ptr<Shader> pShaderProgram)
        : m_pTexture(std::move(pTexture)),
        m_initialSubTexture(std::move(initialSubTexture)),
        m_pShaderProgram(std::move(pShaderProgram))
    {
        // Инициализируем текстурные координаты начальным сабтекстуром
        if (m_pTexture) {
            auto subTexture = m_pTexture->getSubTexture(m_initialSubTexture);
            m_texCoordMin = subTexture.leftBottomUV;
            m_texCoordMax = subTexture.rightTopUV;
        }
    }

    void Sprite::insertFrames(std::vector<FrameDescription> framesDescriptions)
    {
        m_frames = std::move(framesDescriptions);
    }

    void Sprite::setTextureRect(const glm::vec2& min, const glm::vec2& max) {
        m_texCoordMin = min;
        m_texCoordMax = max;
    }

    void Sprite::getTextureCoords(glm::vec2 coords[4]) const {
        coords[0] = glm::vec2(m_texCoordMin.x, m_texCoordMin.y);
        coords[1] = glm::vec2(m_texCoordMax.x, m_texCoordMin.y);
        coords[2] = glm::vec2(m_texCoordMin.x, m_texCoordMax.y);
        coords[3] = glm::vec2(m_texCoordMax.x, m_texCoordMax.y);
    }
