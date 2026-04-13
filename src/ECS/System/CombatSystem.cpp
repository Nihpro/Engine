#include "CombatSystem.h"
#include "../Components/Transform.h"
#include "../Components/Gameplay.h"

void CombatSystem::update(entt::registry& registry) {
    // Игрок атакует монстров (упрощённая версия)
    auto players = registry.view<PlayerTag, Position>();
    auto monsters = registry.view<EnemyTag, Health, Position>();

    if (players.begin() == players.end()) return;

    auto& playerPos = registry.get<Position>(*players.begin());

    for (auto [entity, health, pos] : monsters.each()) {
        float dx = playerPos.value.x - pos.value.x;
        float dy = playerPos.value.y - pos.value.y;
        float distance = glm::length(glm::vec2(dx, dy));

        // Если монстр рядом с игроком
        if (distance < 50.0f) {
            health.current -= 10;

            if (health.current <= 0) {
                registry.emplace<DeadTag>(entity);
            }
        }
    }
}

void CombatSystem::handleCollision(entt::registry& registry,
    entt::entity attacker,
    entt::entity target) {
    // Логика прямого столкновения (для снарядов и т.д.)
    if (auto* health = registry.try_get<Health>(target)) {
        if (auto* monster = registry.try_get<Monster>(attacker)) {
            health->current -= monster->damage;
        }
    }
}