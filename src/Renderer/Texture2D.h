#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <map>


    class Texture2D
    {
    public:
        struct SubTexture {
            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;
        };

        // ResourceManager сам загружает пиксели и передает их сюда!
        Texture2D(const int width, const int height, const unsigned char* data,
            const unsigned int channels, const GLenum filter, const GLenum wrapMode);
        ~Texture2D();

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D(Texture2D&& other) noexcept;
        Texture2D& operator=(Texture2D&& other) noexcept;

        void bind() const;
        void unbind() const;

        // Методы для работы с текстурными атласами
        void addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
        const SubTexture& getSubTexture(const std::string& name) const;

        GLuint getID() const { return ID; }
        int width() const { return m_width; }    // Имя метода изменено под вызов в ResourceManager
        int height() const { return m_height; }  // Имя метода изменено под вызов в ResourceManager
        int getChannels() const { return m_channels; }

    private:
        GLuint ID = 0;
        int m_width = 0;
        int m_height = 0;
        int m_channels = 0;

        std::map<std::string, SubTexture> m_subTextures;
    };
