#pragma once
#include <entt.hpp>

class CleanupSystem {
public:
    void update(entt::registry& registry) {
        auto view = registry.view<DeadTag>();
        for (auto entity : view) {
            registry.destroy(entity);
        }
    }
};