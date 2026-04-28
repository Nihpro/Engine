#pragma once
#include <entt.hpp>
#include "../Components/Transform.h"
#include "../Components/Collision.h"

class CollisionSystem
{
public:
	bool AABB(const Position& posA, const BoxCollider& colA, const Position& posB, const BoxCollider& colB,Position& mtv = Position(0, 0));
	void update(entt::registry& registry, float deltaTime);
};
