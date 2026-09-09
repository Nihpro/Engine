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
	{
		for (auto& element : m_elements) {
			if (element->isActive()) element->update(deltaTime, m_uiScale, glm::vec2(0.f));
		}
	}

	void UIManager::render()
	{
		for (auto& element : m_elements) {
			if (element->isActive()) element->render(this, glm::vec2(0.f));
		}
	}

	void UIManager::DrawScreenElement(const std::string& spriteName, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		auto sprite = ResourceManager::getSprite(spriteName);
		if (sprite) {
			
			auto shader = sprite->getShaderProgram();
			shader->use();
			shader->setMatrix4("projectionMat", m_orthoMatrix);
			shader->setMatrix4("viewMat", glm::mat4(1.0f));

			shader->setVec4("spriteColor", color);

			glm::vec2 centerPosition = position + (size / 2.0f);
			sprite->render(centerPosition, size, 0.f, 1.f);
		}
	}

	void UIManager::DrawWorldElement(const std::string& spriteName, const glm::vec2& position, const glm::vec2& size, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
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

	void UIManager::DrawScreenRect(const glm::vec4& color, const glm::vec2& position, const glm::vec2& size) const
	{
		auto sprite = ResourceManager::getSprite("WhitePixel");
		if (sprite) {
			auto shader = sprite->getShaderProgram();
			shader->use();
			shader->setMatrix4("projectionMat", m_orthoMatrix);
			shader->setMatrix4("viewMat", glm::mat4(1.f));

			shader->setVec4("spriteColor", color);
			glm::vec2 centerPosition = position + (size / 2.0f);
			sprite->render(centerPosition, size, 0.f, 1.f);
		}
	}

	void UIManager::onWindowResize(float width, float height)
	{
		if (height < 1080) {
			m_uiScale = 1.f;
		}
		else if (height >= 1080 && height <= 1440) {
			m_uiScale = 1.5f;
		}
		else if(height >1440){
			m_uiScale = 2.f;
		}
		float virtualWidth = width / m_uiScale;
		float virtualHeight = height / m_uiScale;

		m_orthoMatrix = glm::ortho(0.f, virtualWidth, virtualHeight, 0.f, -1.f, 1.f);
		
		for (auto& element : m_elements) {
			if (element->isActive()) element->updateLayout(glm::vec2(virtualWidth, virtualHeight));
		}
	}
	void UIManager::addElement(std::shared_ptr<Element> element)
	{
		m_elements.push_back(element);
	}
}



