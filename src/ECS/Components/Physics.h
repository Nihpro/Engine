#pragma once

struct PhysicsBody
{
	float mass = 1.f;
	float gravityScale = 1.f;
	bool isKinematic = false;
	bool useGravity = true;
};