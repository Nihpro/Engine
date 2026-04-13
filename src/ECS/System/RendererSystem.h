#pragma once
#include <entt.hpp>
#include <memory>
#include <glm/glm.hpp>

class Renderer;
class Sprite;

class RendererSystem {
public:
    void update(entt::registry& registry, Renderer* renderer);

private:
    // Сортировка по zOrder (можно добавить позже)
    // void sortByZOrder(entt::registry& registry);
};