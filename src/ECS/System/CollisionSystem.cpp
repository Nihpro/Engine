#include "CollisionSystem.h"
#include <algorithm>



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

    // ¬ыбираем ось с минимальным проникновением
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

bool CollisionSystem::CircleAABB(const Position& posA, const CircleCollider& colA, const Position& posB, const BoxCollider& colB, Position& mtv)
{
    float halfWidth = colB.size.x / 2.0f;
    float halfHeight = colB.size.y / 2.0f;
    float closestX = std::max((posB.value.x - halfWidth), std::min(posA.value.x, (posB.value.x + halfWidth)));
    float closestY = std::max((posB.value.y - halfHeight), std::min(posA.value.y, (posB.value.y + halfHeight)));

    glm::vec2 closest(closestX, closestY);
    glm::vec2 diff = posA.value - closest;

    float distSq = diff.x * diff.x + diff.y * diff.y;
    float radiusSq = colA.radius * colA.radius;

    if (distSq >= radiusSq) {
        mtv = Position(0, 0);
        return false;
    }

    float dist = std::sqrt(distSq);
    float depth = colA.radius - dist;


    if (dist > 0.001f) {
        mtv = diff / dist * depth;
    }
    else {
        glm::vec2 toCenter = posA.value - posB.value;

        if (std::abs(toCenter.x) < std::abs(toCenter.y)) {
            mtv = Position((toCenter.x > 0 ? depth : -depth), 0);
        }
        else {
            mtv = Position(0, (toCenter.y > 0 ? depth : -depth));
        }
    }
    return true;
}


void CollisionSystem::update(entt::registry& registry, float deltaTime)
{
    auto view = registry.view<BoxCollider, Position>();
    auto player = registry.view<PlayerTag, CircleCollider, Position>();
    Position mvt;

    for (auto [playerEntity, colA, posA] : player.each()) {
        for (auto [otherEntity, colB, posB] : view.each()) {

            if (playerEntity == otherEntity) {
                continue;
            }

            if (CircleAABB(posA, colA, posB, colB, mvt)) {
                posA.value += mvt.value;

                std::cout << "Yes" << std::endl;
            }
        }
    }
}
