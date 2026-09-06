#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


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

		void DrawScreenElement(const std::string& spriteName, glm::vec2 position, glm::vec2 size);
		void DrawWorldElement(const std::string& spriteName, glm::vec2 position, glm::vec2 size, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

		void onWindowResize(float width, float height);
		

	private:
		glm::mat4 m_orthoMatrix;
	};
}