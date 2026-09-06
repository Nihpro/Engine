#include "UIManager.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/ShaderProgram.h"

namespace UI {
	UIManager::UIManager() : m_orthoMatrix(glm::mat4(1.0f))
	{}

	void UIManager::init()
	{}

	void UIManager::update(float deltaTime)
	{}

	void UIManager::DrawScreenElement(const std::string& spriteName, glm::vec2 position, glm::vec2 size)
	{
		auto sprite = ResourceManager::getSprite(spriteName);
		if (sprite) {
			
			auto shader = sprite->getShaderProgram();
			shader->use();
			shader->setMatrix4("projectionMat", m_orthoMatrix);
			shader->setMatrix4("viewMat", glm::mat4(1.0f));

			sprite->render(position, size, 0.f, 1.f);
		}
	}

	void UIManager::DrawWorldElement(const std::string& spriteName, glm::vec2 position, glm::vec2 size, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
	{
		auto sprite = ResourceManager::getSprite(spriteName);
		if (sprite) {

			auto shader = sprite->getShaderProgram();
			shader->use();
			shader->setMatrix4("projectionMat", projectionMatrix);
			shader->setMatrix4("viewMat", viewMatrix);

			sprite->render(position, size, 0.f, 1.f);
		}
	}

	void UIManager::onWindowResize(float width, float height)
	{
		m_orthoMatrix = glm::ortho(0.f, width, height, 0.f, -1.f, 1.f);
	}
}



