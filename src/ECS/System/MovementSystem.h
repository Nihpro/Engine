#pragma once
#include <entt.hpp>
#include "../Components/Transform.h"
#include <iostream>
#include <cmath>

class MovementSystem {
public:
    void update(entt::registry& registry, float deltaTime) {
        auto view = registry.view<Position, Velocity>();

        for (auto [entity, pos, vel] : view.each()) {
            pos.value += vel.value * deltaTime;
        }
    }
};