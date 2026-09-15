#pragma once
#include "Image.h"
#include <string>
#include <functional>

namespace UI {
	class Button : public Image
	{
	public:
		Button(const std::string spriteName, const glm::vec2 pos, const glm::vec2 size);
		~Button() override = default;

		void update(float deltaTime, float uiScale, glm::vec2 parentPos) override;

		void setButtonColors(const glm::vec4& normal, const glm::vec4& hover, const glm::vec4& pressed) {
			m_normalColor = normal;
			m_hoverColor = hover;
			m_pressedColor = pressed;
		}

		std::function<void()> onClick;
		std::function<void()> onPress;
		std::function<void()> onRelease;
		std::function<void()> onHold;
	protected:
		bool m_isHovered = false;
		bool m_isPressed = false;

		glm::vec4 m_normalColor{ 1.f, 1.f, 1.f, 1.f };
		glm::vec4 m_hoverColor{ 0.8f, 0.8f, 0.8f, 1.f };
		glm::vec4 m_pressedColor{ 0.5f, 0.5f, 0.5f, 1.f };
	};

}