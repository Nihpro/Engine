#pragma once
#include <entt.hpp>
#include "../Components/Transform.h"
#include "../Components/Collision.h"

class CollisionSystem
{
public:
	void update(entt::registry& registry, float deltaTime);

	bool AABB(const Position& posA, const BoxCollider& colA, const Position& posB, const BoxCollider& colB,Position& mtv);
	bool CircleAABB(const Position& posA, const CircleColider& colA, const Position& posB, const BoxCollider& colB, Position& mtv);
	
	
	
};
