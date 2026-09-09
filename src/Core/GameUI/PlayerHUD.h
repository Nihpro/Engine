#pragma once
#include "../UI/Panel.h"

namespace Core {
	class PlayerHUD : public UI::Panel
	{
	public:
		PlayerHUD(glm::vec2 windowSize);

		void updateLayout(const glm::vec2& screenSize) override {
			m_size = screenSize;
			UI::Panel::updateLayout(screenSize);
		}
	};
}