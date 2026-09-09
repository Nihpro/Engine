#include "OpenGLShaderProgram.h"
#include<glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace RenderEngine;
namespace RenderOpenGL {

    static GLenum DataTypeInBaseType(ShaderType type) {

        switch (type)
        {
        case ShaderType::Fragment_shader:
            return GL_FRAGMENT_SHADER;
            break;
        case ShaderType::Vertex_shader:
            return GL_VERTEX_SHADER;
            break;
        }
        return 0;
    }

    OpenGLShaderProgram::OpenGLShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderID;
        if (!createShader(vertexShader, ShaderType::Vertex_shader, vertexShaderID))
        {
            std::cerr << "VERTEX SHADER compile-time error" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if (!createShader(fragmentShader, ShaderType::Fragment_shader, fragmentShaderID))
        {
            std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    OpenGLShaderProgram::~OpenGLShaderProgram()
    {
        glDeleteProgram(m_ID);
    }
    int OpenGLShaderProgram::getUniformLocation(const std::string& name) const
    {
        auto it = uniformLocationCache.find(name);
        if (it != uniformLocationCache.end()) {
            return it->second;
        }

        int location = glGetUniformLocation(m_ID, name.c_str());
        uniformLocationCache[name] = location;
        return location;
    }
    void OpenGLShaderProgram::use() const
    {
        glUseProgram(m_ID);
    }
    void OpenGLShaderProgram::setInt(const std::string & name, const int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }
    void OpenGLShaderProgram::setFloat(const std::string & name, const float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }
    void OpenGLShaderProgram::setMatrix4(const std::string & name, const glm::mat4 & matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShaderProgram::setVec4(const std::string& name, const glm::vec4& value) {
        glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }
    bool OpenGLShaderProgram::createShader(const std::string& source, const ShaderType shaderType, uint32_t& shaderID)
    {
        shaderID = glCreateShader(DataTypeInBaseType(shaderType));
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }
}
