#pragma once

#include <entt.hpp>
#include <memory>
#include "Components/Transform.h"
#include "Components/Gameplay.h"
#include "Components/Render.h"
#include "Components/Collision.h"

#include "System/AnimationSystem.h"
#include "System/MovementSystem.h"
#include "System/RendererSystem.h"
#include "System/PlayerControlSystem.h"
#include "System/CollisionSystem.h"



class ECSManager
{
public:

	ECSManager();

    void init();
    void update(float deltaTime);
    void processInput();
    void render();
    glm::vec2 getPlayerPosition();
    entt::registry& getRegistry() { return m_registry; }

private:
    // ECS
    entt::registry m_registry;

    // ECS системы
    std::unique_ptr<MovementSystem> m_movementSystem;
    std::unique_ptr<RendererSystem> m_renderSystem;
    std::unique_ptr<AnimationSystem> m_animationSystem;
    std::unique_ptr<PlayerControlSystem> m_playerControlSystem;
    std::unique_ptr<CollisionSystem> m_collisionSystem;

    void initGameObjects();
};
