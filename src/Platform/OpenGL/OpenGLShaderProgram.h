#pragma once
#include "../../Renderer/ShaderProgram.h"

namespace RenderOpenGL {

	class OpenGLShaderProgram : public RenderEngine::ShaderProgram
	{
	public:
		OpenGLShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~OpenGLShaderProgram() override;

	private:
		bool m_isCompiled = false;
		uint32_t m_ID = 0;
		mutable std::unordered_map<std::string, int> uniformLocationCache;

		// Унаследовано через ShaderProgram
		int getUniformLocation(const std::string& name) const override;
		bool isCompiled() const override { return m_isCompiled; };
		void use() const override;
		void setInt(const std::string& name, const int value) override;
		void setFloat(const std::string& name, const float value) override;
		void setMatrix4(const std::string& name, const glm::mat4& matrix) override;
		bool createShader(const std::string& source, const RenderEngine::ShaderType shaderType, uint32_t& shaderID) override;
	};

}