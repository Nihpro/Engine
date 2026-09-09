#include "PlayerHUD.h"	
#include "../UI/Image.h"
#include "../UI/Button.h"
#include <iostream>

namespace Core {
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

		auto inventory = std::make_shared<UI::Panel>(glm::vec2(0), glm::vec2(400, 300));
		inventory->setColor(glm::vec4(0.f, 0.f, 0.f, 0.7f));
		inventory->setAnchor(UI::Anchor::TopLeft);
		inventory->setOffset(glm::vec2(0.f, 0.f));
		this->addChild(inventory);
		
	}
}