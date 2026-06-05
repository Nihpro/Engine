#pragma once
#include <entt.hpp>
#include "../Components/Physics.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"

class PhysicsSystem
{
public:
	void update(entt::registry& registry, float deltaTime);


};
