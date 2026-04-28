#pragma once
#include <entt.hpp>


class PlayerControlSystem
{
public:
	
	void processInput(entt::registry& registry);
	void setSpeed(float speed) { this->speed = speed; }
private:
	float speed = 200.f;
};