#pragma once
#include <glm/glm.hpp>
namespace UI
{
	class UIManager;

	enum class Anchor { TopLeft, TopRight, BottomLeft, BottomRight, Center };

	class Element
	{
	public:
		Element(const glm::vec2& position, const glm::vec2& size);
		virtual ~Element() = default;

		virtual void update(float deltaTime, float uiScale = 1.f, glm::vec2 parentPos = glm::vec2(0.f)) = 0;
		virtual void render(UIManager* uiManager, glm::vec2 parentPos = glm::vec2(0.f)) = 0;

		void setPosition(const glm::vec2& pos) { m_position = pos; }
		void setSize(const glm::vec2& size) { m_size = size; }
		void setColor(const glm::vec4& color) { m_color = color; }
		void setActive(const bool active) { m_isActive = active; }
		void setAnchor(Anchor anchor) { m_anchor = anchor; }
		void setOffset(const glm::vec2& offset) { m_offset = offset; }

		virtual void updateLayout(const glm::vec2& screenSize);

		glm::vec2 getPosition() const { return m_position; }
		glm::vec2 getSize() const { return m_size; }
		glm::vec4 getColor() const { return m_color; }
		bool isActive() const { return m_isActive; }

	protected:
		glm::vec4 m_color{ 1.f, 1.f, 1.f, 1.f };
		glm::vec2 m_position{ 0 };
		glm::vec2 m_size{ 0 };
		bool m_isActive{ true };
		Anchor m_anchor = Anchor::TopLeft;
		glm::vec2 m_offset{ 0.f,0.f };
	};

}
