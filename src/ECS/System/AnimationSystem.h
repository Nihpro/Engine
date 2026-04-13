#pragma once
#include <entt.hpp>

class AnimationSystem {
public:
    void update(entt::registry& registry, float deltaTime);
};