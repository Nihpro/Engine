#pragma once

#include "../UI/Panel.h"


namespace GameUI {
	class Inventory : public UI::Panel
	{
	public:
		Inventory(const glm::vec2& pos, const glm::vec2& size, const int col, const int row);
		
		void setCountSlot(int count);


		~Inventory() override = default;

	private:
		void buildGrid();
		int m_colSlot, m_rowSlot;
		int m_countSlot = 5, m_countSlotMax;
	};
}