#pragma once
#include <string>

using namespace std;

struct Info
{
    string name;
};

struct Health
{
	int current = 100;
	int max = 100;

	Health() = default;
	Health(int hp) : current(hp), max(hp) {}
	Health(int current, int max) : current(current), max(max) {}

	bool isAlive() const { return current > 0; }
	float getPercentage() const { return static_cast<float>(current) / max; }
};

struct Player {
    int mana = 100;
    int level = 1;
    int experience = 0;
};

struct Monster {
    int damage = 10;
    int expReward = 20;
    entt::hashed_string type;  // "slime", "goblin", "dragon"
};

struct Item {
    int itemId = 0;
    int count = 1;
};

struct Projectile {
    float damage = 25.0f;
    float lifetime = 3.0f;
    float speed = 500.0f;
};

// Маркеры (пустые компоненты)
struct PlayerTag {};
struct EnemyTag {};
struct DeadTag {};