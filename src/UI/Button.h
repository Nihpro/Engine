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

		std::function<void()> onClick;
		std::function<void()> onPress;
		std::function<void()> onRelease;
		std::function<void()> onHold;
	protected:
		bool m_isHovered = false;
		bool m_isPressed = false;
	};

}