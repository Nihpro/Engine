#pragma once
#include "../UI/Button.h"
#include "../UI/Image.h"
#include <memory>

namespace GameUI {
	class InventorySlot : public UI::Button
	{
	public:
		InventorySlot(const std::string spriteName, const glm::vec2 pos, const glm::vec2 size);
		~InventorySlot() override = default;

		void render(UI::UIManager* uiManager, glm::vec2 parentPos) override;
		void setId(const int id) { m_slotId = id; }
		int getId() const { return m_slotId; }

	private:
		int m_itemId = -1;
		int m_count = 0;
		int m_slotId = 0;

		std::shared_ptr<UI::Image> m_itemIcon;
	};
}