#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Element.h"


namespace UI {
	class UIManager
	{
	public:
		UIManager();
		~UIManager() = default;

		UIManager(const UIManager&) = delete;
		UIManager& operator=(const UIManager&) = delete;


		void init();
		void update(float deltaTime);
		void render();

		void DrawScreenElement(const std::string& spriteName, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.f));
		void DrawWorldElement(const std::string& spriteName, const glm::vec2& position, const glm::vec2& size, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		void DrawScreenRect(const glm::vec4& color, const glm::vec2& position, const glm::vec2& size) const;

		void onWindowResize(float width, float height);

		void addElement(std::shared_ptr<Element> element);
		

	private:
		glm::mat4 m_orthoMatrix;
		std::vector<std::shared_ptr<Element>> m_elements;
		float m_uiScale = 1.f;
	};
}