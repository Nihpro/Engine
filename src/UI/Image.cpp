#include "Image.h"
#include "UIManager.h"

namespace UI {

	Image::Image(const std::string spriteName, glm::vec2 position, glm::vec2 size) : m_spriteName(spriteName), Element(position, size)
	{}

	void Image::update(float deltaTime, float uiScale, glm::vec2 parentPos)
	{}

	void Image::render(UIManager* uiManager, glm::vec2 parentPos)
	{
		glm::vec2 absolutPos = parentPos + m_position;
		uiManager->DrawScreenElement(m_spriteName, absolutPos, m_size, m_color);
	}
}