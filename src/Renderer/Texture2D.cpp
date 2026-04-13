#include "Texture2D.h"
#include <iostream>


    Texture2D::Texture2D(const int width, const int height, const unsigned char* data,
        const unsigned int channels, const GLenum filter, const GLenum wrapMode)
        : m_width(width), m_height(height), m_channels(channels)
    {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        if (data)
        {
            GLenum format = GL_RGB;
            if (channels == 4) format = GL_RGBA;
            else if (channels == 1) format = GL_RED;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Texture2D Warning: loaded with empty data!" << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture2D::Texture2D(Texture2D&& other) noexcept
        : ID(other.ID), m_width(other.m_width), m_height(other.m_height),
        m_channels(other.m_channels), m_subTextures(std::move(other.m_subTextures))
    {
        other.ID = 0;
    }

    Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteTextures(1, &ID);
            ID = other.ID;
            m_width = other.m_width;
            m_height = other.m_height;
            m_channels = other.m_channels;
            m_subTextures = std::move(other.m_subTextures);
            other.ID = 0;
        }
        return *this;
    }

    void Texture2D::bind() const { glBindTexture(GL_TEXTURE_2D, ID); }
    void Texture2D::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

    Texture2D::~Texture2D() { glDeleteTextures(1, &ID); }

    void Texture2D::addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV)
    {
        m_subTextures.emplace(std::move(name), SubTexture{ leftBottomUV, rightTopUV });
    }

    const Texture2D::SubTexture& Texture2D::getSubTexture(const std::string& name) const
    {
        auto it = m_subTextures.find(name);
        if (it != m_subTextures.end()) {
            return it->second;
        }

        // Возвращаем дефолтную если не найдено (вся текстура целиком)
        static SubTexture defaultSubTexture = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
        return defaultSubTexture;
    }
