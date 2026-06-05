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

        if (std::abs(toCenter.x) > std::abs(toCenter.y)) {
            mtv = Position((toCenter.x > 0 ? depth : -depth), 0);
        }
        else {
            mtv = Position(0, (toCenter.y > 0 ? depth : -depth));
        }
    }
    return true;
}

bool CollisionSystem::PointAABB(const Position& posA, const PointCollider& point, const Position& posB, const BoxCollider& colB, Position& mtv) {

    // 0. ВЫЧИСЛЯЕМ МИРОВУЮ ПОЗИЦИЮ ТОЧКИ (Позиция сущности + смещение коллайдера)
    float pointWorldX = posA.value.x + point.offset.x;
    float pointWorldY = posA.value.y + point.offset.y;

    // 1. Находим границы квадрата (в мировых координатах)
    float halfWidth = colB.size.x / 2.0f;
    float halfHeight = colB.size.y / 2.0f;

    float minX = posB.value.x - halfWidth;
    float maxX = posB.value.x + halfWidth;
    float minY = posB.value.y - halfHeight;
    float maxY = posB.value.y + halfHeight;

    // 2. Проверяем попадание МИРОВОЙ позиции точки в границы
    if (pointWorldX < minX || pointWorldX > maxX ||
        pointWorldY < minY || pointWorldY > maxY) {
        mtv = Position(0.0f, 0.0f); // Коллизии нет
        return false;
    }

    // 3. Вычисляем MTV (используя мировую позицию точки)
    float distLeft = pointWorldX - minX;
    float distRight = maxX - pointWorldX;
    float distBottom = pointWorldY - minY;
    float distTop = maxY - pointWorldY;

    // Ищем самое маленькое расстояние
    float minDist = std::min({ distLeft, distRight, distBottom, distTop });

    // Назначаем вектор выталкивания (MTV)
    if (minDist == distLeft) {
        mtv = Position(-distLeft, 0.0f);
    }
    else if (minDist == distRight) {
        mtv = Position(distRight, 0.0f);
    }
    else if (minDist == distBottom) {
        mtv = Position(0.0f, -distBottom);
    }
    else {
        mtv = Position(0.0f, distTop);
    }

    return true;
}

#include "../Components/Physics.h"
void CollisionSystem::update(entt::registry& registry, float deltaTime)
{
	auto view = registry.view<BoxCollider, Position>();
    auto player = registry.view<PlayerTag, CircleCollider, Position, PointCollider, PhysicsBody>();
    Position mvt;

    

    for (auto [playerEntity, colA, posA, point, ph] : player.each()) {
        bool isGrounded = false;
        for (auto [otherEntity, colB, posB] : view.each()) {

            if (playerEntity == otherEntity) {
                continue;
            }

            if (CircleAABB(posA, colA, posB, colB, mvt)) {
                if(!colA.isTrigger && !colB.isTrigger)
                {
                    posA.value += mvt.value;
                    if (registry.all_of<Velocity>(playerEntity)) {
                        auto& vel = registry.get<Velocity>(playerEntity).value;
                        // Если выталкивание в основном вертикальное (пол/потолок)
                        if (std::abs(mvt.value.y) > std::abs(mvt.value.x)) {
                            if (mvt.value.y > 0.0001f && vel.y < 0) {
                                vel.y = 0; // На земле
                                ph.useGravity = false;
                            }
                            if (mvt.value.y < -0.0001f && vel.y > 0) vel.y = 0; // Удар головой
                        } 
                        // Если в основном горизонтальное (стена)
                        else {
                            if (mvt.value.x > 0.0001f && vel.x < 0) vel.x = 0; // Уперлись в левую стену
                            if (mvt.value.x < -0.0001f && vel.x > 0) vel.x = 0; // Уперлись в правую стену
                        }
                    }
                }
            }
            if (!point.isTrigger && !colB.isTrigger)
            {
                if (PointAABB(posA, point, posB, colB, mvt)) {
                    std::cout << "Point yes " << registry.get<Info>(otherEntity).name << std::endl;
                    isGrounded = true;
                }
                else {
                    // Временно выводи координаты, чтобы увидеть, почему они не пересекаются
                    float pX = posA.value.x + point.offset.x;
                    float pY = posA.value.y + point.offset.y;
                    float halfW = colB.size.x / 2.0f;
                    float halfH = colB.size.y / 2.0f;

                    // Если точка близко, но не попадает, ты увидишь это в логах
                    if (std::abs(pX - posB.value.x) < 50.f) {
                        std::cout << "Point cucut: " << pX << "," << pY << " Block: " << posB.value.x << "," << posB.value.y << "\n";
                    }
                }
            }
        }
        ph.useGravity = !isGrounded;

    }

}
