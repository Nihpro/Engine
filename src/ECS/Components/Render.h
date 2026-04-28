#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace RenderEngine {
    class Sprite;
}

struct Renderable {
    std::shared_ptr<RenderEngine::Sprite> sprite = nullptr;
    glm::vec2 size = glm::vec2(32.0f, 32.0f);
    float rotation = 0.0f;
    glm::vec3 color = glm::vec3(1.0f);
    bool visible = true;
    int layer = 0;  // для сортировки отрисовки
    size_t currentFrame = 0;

    Renderable() = default;
    Renderable(std::shared_ptr<RenderEngine::Sprite> spr) : sprite(spr) {}
    Renderable(std::shared_ptr<RenderEngine::Sprite> spr, const glm::vec2& sz)
        : sprite(spr), size(sz) {}
};