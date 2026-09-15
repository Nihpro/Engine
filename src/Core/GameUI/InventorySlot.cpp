#include "InventorySlot.h"

namespace GameUI {
	InventorySlot::InventorySlot(const std::string spriteName, const glm::vec2 pos, const glm::vec2 size) : UI::Button(spriteName, pos, size)
	{
		glm::vec2 iconOffset(5.f, 5.f);
		glm::vec2 iconSize = size - glm::vec2(10.f, 10.f);

		m_itemIcon = std::make_shared<UI::Image>("", iconOffset, iconSize);
	}
	void InventorySlot::render(UI::UIManager* uiManager, glm::vec2 parentPos)
	{
		UI::Button::render(uiManager, parentPos);

		glm::vec2 absolutePos = parentPos + m_position;

		if (m_itemId != -1) {
			m_itemIcon->render(uiManager, absolutePos);
		}

	}
}