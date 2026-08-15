#pragma once

#include "../Renderer/OpenGL.h"
#include <string>
#include <glm/mat4x4.hpp>
#include <unordered_map>

namespace RenderEngine {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();

        GLint getUniformLocation(const std::string& name) const;

        bool isCompiled() const { return m_isCompiled; }
        void use() const;
        void setInt(const std::string& name, const GLint value);
        void setFloat(const std::string& name, const GLfloat value);
        void setMatrix4(const std::string& name, const glm::mat4& matrix);

        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

    private:
        bool createShader(const std::string& source, const GLenum shaderType, uint32_t& shaderID);

        bool m_isCompiled = false;
        uint32_t m_ID = 0;

        mutable std::unordered_map<std::string, GLint> uniformLocationCache;
    };
}
