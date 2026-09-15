#include "Inventory.h"
#include "InventorySlot.h"
#include <iostream>

namespace GameUI {
	Inventory::Inventory(const glm::vec2& pos, const glm::vec2& size, const int col, const int row) : UI::Panel(pos, size), m_colSlot(col), m_rowSlot(row)
	{
		m_countSlotMax = m_colSlot * m_rowSlot;
		std::cout << "SlotMax [" << m_countSlotMax << "]\n";
		float panelWidth = (m_colSlot * 50.f) + ((m_colSlot + 1) * 5.f);
		float panelHeight = (m_rowSlot * 50.f) + ((m_rowSlot + 1) * 5.f);
		m_size = glm::vec2(panelWidth, panelHeight);

		buildGrid();
	}
	void Inventory::setCountSlot(int count)
	{
		m_countSlot = count;
		m_children.clear();
		buildGrid();

	}
	void Inventory::buildGrid()
	{
		for (int i = 0; i < m_countSlot && i < m_countSlotMax; ++i) {
			int row = i / m_colSlot;
			int col = i % m_colSlot;

			auto slot = std::make_shared<InventorySlot>("Default", glm::vec2(0), glm::vec2(50, 50));
			slot->setButtonColors(
				glm::vec4(0.25f, 0.25f, 0.25f, 0.7f),
				glm::vec4(0.30f, 0.30f, 0.30f, 0.7f),
				glm::vec4(0.20f, 0.20f, 0.20f, 0.8f)
			);
			glm::vec2 slotOffset(((col * 50)), ((row * 50)));
			slot->setOffset(glm::vec2(5.f + col * 5.f, 5.f + row * 5.f) + slotOffset);
			slot->setId(i);
			slot->onClick = [i]() {
				std::cout << "Slot id [" << i << "]\n";
				};

			this->addChild(slot);
		}
		
	}
}