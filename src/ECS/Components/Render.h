#pragma once
#include <memory>
#include <glm/glm.hpp>

class Sprite;

struct Renderable {
    std::shared_ptr<Sprite> sprite = nullptr;
    glm::vec2 size = glm::vec2(32.0f, 32.0f);
    float rotation = 0.0f;
    glm::vec3 color = glm::vec3(1.0f);
    bool visible = true;
    int zOrder = 0;  // для сортировки отрисовки

    Renderable() = default;
    Renderable(std::shared_ptr<Sprite> spr) : sprite(spr) {}
    Renderable(std::shared_ptr<Sprite> spr, const glm::vec2& sz)
        : sprite(spr), size(sz) {}
};