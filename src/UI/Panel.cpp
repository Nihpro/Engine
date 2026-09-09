#include "Panel.h"
#include "UIManager.h"

namespace UI {
	Panel::Panel(const glm::vec2& pos, const glm::vec2& size) : Element(pos, size)
	{
		m_color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	void Panel::update(float deltaTime, float uiScale, glm::vec2 parentPos)
	{
		glm::vec2 absolutPos = parentPos + m_position;

		for (auto& child : m_children) 
			if(child->isActive()) 
			{
				child->update(deltaTime,uiScale, absolutPos);
				child->updateLayout(m_size);
			}
	}
	void Panel::render(UIManager* uiManager, glm::vec2 parentPos)
	{
		glm::vec2 absolutPos = parentPos + m_position;

		if (m_color.a > 0.f) {
			uiManager->DrawScreenRect(m_color, absolutPos, m_size);
		}
		for (auto& child : m_children)
			if (child->isActive())
				child->render(uiManager, absolutPos);
	}
	void Panel::addChild(std::shared_ptr<Element> child)
	{
		m_children.push_back(child);
	}
}