#include "PlayerHUD.h"	
#include "../UI/Image.h"
#include "../UI/Button.h"
#include "InventorySlot.h"
#include "Inventory.h"
#include <iostream>

namespace GameUI {
	PlayerHUD::PlayerHUD(glm::vec2 windowSize) : UI::Panel(glm::vec2(0), windowSize)
	{
		auto image1 = std::make_shared<UI::Image>("Box", glm::vec2(0),glm::vec2(50, 50));
		image1->setColor(glm::vec4(.5f, .5f, .5f, 0.5f));
		image1->setAnchor(UI::Anchor::BottomRight);
		image1->setOffset(glm::vec2(0, 0));
		this->addChild(image1);

		auto button1 = std::make_shared<UI::Button>("Box", glm::vec2(0), glm::vec2(50, 50));
		button1->onClick = [](){
			std::cout << "Yes Press\n";
			};
		button1->onHold = []() {
			std::cout << "Zajal\n";
			};
		button1->onRelease = []() {
			std::cout << "Otjal\n";
			};
		button1->onPress = []() {
			std::cout << "najal\n";
			};
		button1->setAnchor(UI::Anchor::BottomRight);
		button1->setOffset(glm::vec2(50, 0));
		this->addChild(button1);

		auto panel1 = std::make_shared<UI::Panel>(glm::vec2(0), glm::vec2(390, 300));
		panel1->setColor(glm::vec4(0.f, 0.f, 0.f, 0.7f));
		panel1->setAnchor(UI::Anchor::TopRight);
		panel1->setOffset(glm::vec2(15.f, 15.f));

		int num = 7;
		int row = -1, col = 0;//ряд и столбцы
		for (int i = 0; i < 30; ++i, ++col) {
			row = i / num;
			col = i % num;

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
				std::cout << "Slot id ["<<i<<"]\n";
				};

			panel1->addChild(slot);
		}
		
		this->addChild(panel1);

		auto inventory = std::make_shared<Inventory>(glm::vec2(0), glm::vec2(390, 300), 5, 4);
		inventory->setColor(glm::vec4(0.f, 0.f, 0.f, 0.7f));
		inventory->setAnchor(UI::Anchor::TopLeft);
		inventory->setOffset(glm::vec2(15.f, 15.f));
		inventory->setCountSlot(15);
		this->addChild(inventory);


		
	}
}