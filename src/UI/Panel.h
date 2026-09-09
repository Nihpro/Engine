#pragma once
#include "Element.h"
#include <vector>
#include <memory>

namespace UI {
	class Panel : public Element
	{
	public:
		Panel(const glm::vec2& pos, const glm::vec2& size);
		~Panel() override = default;

		void update(float deltaTime, float uiScale, glm::vec2 parentPos) override;
		void render(UIManager* uiManager, glm::vec2 parentPos) override;


		void addChild(std::shared_ptr<Element> child);

	protected:
		std::vector<std::shared_ptr<Element>> m_children;
	};

}