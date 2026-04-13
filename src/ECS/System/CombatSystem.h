#pragma once
#include <entt.hpp>

class CombatSystem {
public:
    void update(entt::registry& registry);

private:
    void handleCollision(entt::registry& registry,
        entt::entity attacker,
        entt::entity target);
};