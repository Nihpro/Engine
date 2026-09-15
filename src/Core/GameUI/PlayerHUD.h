#pragma once
#include "../UI/Panel.h"

namespace GameUI {
	class PlayerHUD : public UI::Panel
	{
	public:
		PlayerHUD(glm::vec2 windowSize);
		~PlayerHUD() override = default;

		void updateLayout(const glm::vec2& screenSize) override {
			m_size = screenSize;
			UI::Panel::updateLayout(screenSize);
		}
	};
}