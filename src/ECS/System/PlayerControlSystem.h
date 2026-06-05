#pragma once
#include <entt.hpp>


class PlayerControlSystem
{
public:
	
	void processInput(entt::registry& registry, float deltaTime);
private:
	float maxSpeed = 300.f;
	float acceleration = 1200.f;
};