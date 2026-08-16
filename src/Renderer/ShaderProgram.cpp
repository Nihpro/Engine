#include "ShaderProgram.h"
#include "../Platform/OpenGL/OpenGLShaderProgram.h"

namespace RenderEngine {
	std::unique_ptr<ShaderProgram> ShaderProgram::Create(const std::string& vertexShader, const std::string& fragmentShader)
	{
		return std::make_unique<RenderOpenGL::OpenGLShaderProgram>(vertexShader, fragmentShader);
	}
}