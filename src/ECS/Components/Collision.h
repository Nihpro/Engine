#pragma once
#include <glm/glm.hpp>

struct BaseCollider {
	bool isTrigger = false;
	entt::hashed_string name;
	glm::vec2 offset = glm::vec2(0.0f);
};

struct BoxCollider : BaseCollider
{
	glm::vec2 size = glm::vec2(0.0f);
	
};
struct CircleCollider : BaseCollider
{
	float radius = 0.f;
	
};

struct PointCollider : BaseCollider
{

};