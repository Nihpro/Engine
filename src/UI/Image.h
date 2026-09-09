#pragma once
#include "Element.h"
#include <string>

namespace UI {
	class Image : public Element
	{
	public:

		Image(const std::string spriteName, glm::vec2 position, glm::vec2 size);
		~Image() override = default;

		void update(float deltaTime, float uiScale, glm::vec2 parentPos) override;
		void render(UIManager* uiManager, glm::vec2 parentPos) override;

		void setSprite(const std::string& spriteName) { m_spriteName = spriteName; }
		std::string getSprite() const { return m_spriteName; }

	protected:
		std::string m_spriteName;
	};

}