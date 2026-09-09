#pragma once
#include <string>
#include <glm/mat4x4.hpp>
#include <unordered_map>
#include <memory>

namespace RenderEngine {
    enum class ShaderType {
        Vertex_shader,
        Fragment_shader
    };

    class ShaderProgram {
    public:
        ShaderProgram() = default;
        virtual ~ShaderProgram() = default;

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        virtual int getUniformLocation(const std::string& name) const = 0;
        virtual bool isCompiled() const = 0;
        virtual void use() const = 0;
        virtual void setInt(const std::string& name, const int value) = 0;
        virtual void setFloat(const std::string& name, const float value) = 0;
        virtual void setMatrix4(const std::string& name, const glm::mat4& matrix) = 0;
        virtual void setVec4(const std::string& name, const glm::vec4& value) = 0;

        static std::unique_ptr<ShaderProgram> Create(const std::string& vertexShader, const std::string& fragmentShader);

    private:
        virtual bool createShader(const std::string& source, const ShaderType shaderType, uint32_t& shaderID) = 0;

    };
}
