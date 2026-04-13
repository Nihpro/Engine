#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <vector>

class GameObject {
public:
    GameObject(const std::string& name = "");
    virtual ~GameObject() = default;

    virtual void start() {}
    virtual void update(float deltaTime) {}
    virtual void render(class Renderer& renderer) {}

    // Transform
    void setPosition(const glm::vec2& position) { m_position = position; }
    void setRotation(float rotation) { m_rotation = rotation; }
    void setScale(const glm::vec2& scale) { m_scale = scale; }

    glm::vec2 getPosition() const { return m_position; }
    float getRotation() const { return m_rotation; }
    glm::vec2 getScale() const { return m_scale; }

    // Hierarchy
    void setParent(GameObject* parent);
    void addChild(std::unique_ptr<GameObject> child);
    void removeChild(GameObject* child);

    GameObject* getParent() const { return m_parent; }
    const std::vector<std::unique_ptr<GameObject>>& getChildren() const { return m_children; }

    // Name
    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }

    // Active
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }

    glm::mat4 getTransformMatrix() const;

protected:
    std::string m_name;
    glm::vec2 m_position = { 0.0f, 0.0f };
    float m_rotation = 0.0f;
    glm::vec2 m_scale = { 1.0f, 1.0f };

    GameObject* m_parent = nullptr;
    std::vector<std::unique_ptr<GameObject>> m_children;

    bool m_active = true;
};