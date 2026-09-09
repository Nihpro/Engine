#include "Element.h"
namespace UI
{
	Element::Element(const glm::vec2& position, const glm::vec2& size) : m_position(position), m_size(size)
	{}
	void Element::updateLayout(const glm::vec2 & screenSize)
	{
		switch (m_anchor)
		{
		case Anchor::TopLeft:
			m_position = m_offset;
			break;
		case Anchor::TopRight:
			m_position = glm::vec2(screenSize.x - m_size.x - m_offset.x, m_offset.y);
			break;
		case Anchor::BottomLeft:
			m_position = glm::vec2(m_offset.x, screenSize.y - m_size.y - m_offset.y);
			break;
		case Anchor::BottomRight:
			m_position = screenSize - m_size - m_offset;
			break;
		case Anchor::Center:
			m_position = (screenSize / 2.f) - (m_size / 2.f) + m_offset;
			break;
		default:
			break;
		}
	}
}
