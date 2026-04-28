#include "CollisionSystem.h"


#include "../Components/Gameplay.h"
#include <iostream>

bool CollisionSystem::AABB(
    const Position& posA,
    const BoxCollider& colA,
    const Position& posB,
    const BoxCollider& colB,
    Position& mtv
) {

    float dx = posB.value.x - posA.value.x;
    float px = (colA.size.x / 2.0f + colB.size.x / 2.0f) - std::abs(dx);

    if (px <= 0.0f)
        return false;

    float dy = posB.value.y - posA.value.y;
    float py = (colA.size.y / 2.0f + colB.size.y / 2.0f) - std::abs(dy);

    if (py <= 0.0f)
        return false;

    // Выбираем ось с минимальным проникновением
    if (px < py) {

        mtv.value.x = (dx < 0.0f) ? -px : px;
        mtv.value.y = 0.0f;

    }
    else {

        mtv.value.x = 0.0f;
        mtv.value.y = (dy < 0.0f) ? -py : py;
    }

    return true;
}


void CollisionSystem::update(entt::registry& registry, float deltaTime)
{
	auto view = registry.view<BoxCollider, Position>();
    auto player = registry.view<PlayerTag, BoxCollider, Position>();
    Position mvt;

    for (auto [playerEntity, colA, posA] : player.each()) {
        for (auto [otherEntity, colB, posB] : view.each()) {

            if (playerEntity == otherEntity) {
                continue;
            }

            if (AABB(posA, colA, posB, colB, mvt)) {
               posA.value.x -= mvt.value.x;
                posA.value.y -= mvt.value.y;
                std::cout << "Yes" << std::endl;
            }
        }
    }
}
