#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(const std::string& name)
    : m_name(name) {}

void GameObject::setParent(GameObject* parent) {
    if (m_parent) {
        auto& siblings = m_parent->m_children;
        siblings.erase(std::remove_if(siblings.begin(), siblings.end(),
            [this](const std::unique_ptr<GameObject>& child) {
                return child.get() == this;
            }), siblings.end());
    }

    m_parent = parent;
}

void GameObject::addChild(std::unique_ptr<GameObject> child) {
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

void GameObject::removeChild(GameObject* child) {
    m_children.erase(std::remove_if(m_children.begin(), m_children.end(),
        [child](const std::unique_ptr<GameObject>& c) {
            return c.get() == child;
        }), m_children.end());
}

glm::mat4 GameObject::getTransformMatrix() const {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(m_position, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(m_scale, 1.0f));

    if (m_parent) {
        transform = m_parent->getTransformMatrix() * transform;
    }

    return transform;
}