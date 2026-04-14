#pragma once

#include "OpenGL.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>


class Shader
{
public:
    // ResourceManager передает сюда сам КОД шейдера, а не пути к файлам!
    Shader(const std::string& vertexCode, const std::string& fragmentCode);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&&) noexcept;
    Shader& operator=(Shader&&) noexcept;

    GLint getUniformLocation(const std::string& name) const;
    bool isCompiled() const { return m_isCompiled; }
    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMatrix4fv(const std::string& name, const glm::mat4& value) const;

private:
    mutable std::unordered_map<std::string, GLint> uniformLocationCache;
    bool m_isCompiled = false;
    GLuint ID = 0;
};
