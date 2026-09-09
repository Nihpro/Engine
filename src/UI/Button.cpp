#include "Button.h"
#include "../Input/InputManager.h"
namespace UI {
	Button::Button(const std::string spriteName, const glm::vec2 pos, const glm::vec2 size) : Image(spriteName, pos, size)
	{}
	void Button::update(float deltaTime, float uiScale, glm::vec2 parentPos)
	{
		float rawX, rawY;
		InputManager::getMousePosition(rawX, rawY);

		float x = rawX / uiScale;
		float y = rawY / uiScale;

		glm::vec2 absolutePos = parentPos + m_position;
		bool isHoverNow = (x >= absolutePos.x && x <= absolutePos.x + m_size.x &&
			y >= absolutePos.y && y <= absolutePos.y + m_size.y);

		if (isHoverNow) {
			m_isHovered = true;

			//Нажим
			if (InputManager::isMouseButtonJustPressed(0)) {
				m_isPressed = true;
				if (onPress) onPress();
			}

			//Зажатие
			if (InputManager::isMouseButtonPressed(0)) {
				if (m_isPressed && onHold) {
					onHold();
				}
			}

			//Отжатие и полный клик
			if (InputManager::isMouseButtonReleased(0)) {
				if (onRelease) onRelease();

				if (m_isPressed) {
					if (onClick) onClick();
				}
				m_isPressed = false;
			}

			//Визуальный отклик
			if (m_isPressed) {
				m_color = glm::vec4(0.5f, 0.5f, 0.5f, 1.f);
			}
			else {
				m_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.f); 
			}
		}
		else {
			m_isHovered = false;
			m_color = glm::vec4(1.f, 1.f, 1.f, 1.f);

			// Защита от залипания
			if (InputManager::isMouseButtonReleased(0)) {
				m_isPressed = false;
			}
		}
	}
}

