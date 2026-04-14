#pragma once

#include <entt.hpp>
#include <memory>
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/Gameplay.h"
#include "../ECS/Components/Render.h"
#include "../ECS/System/AnimationSystem.h"
#include "../ECS/System/CleanupSystem.h"
#include "../ECS/System/CombatSystem.h"
#include "../ECS/System/MovementSystem.h"
#include "../ECS/System/RendererSystem.h"


class ECSManager
{
public:

	ECSManager();

    void init();
    void processInput();
    void update(float deltaTime);
    void render(Renderer* render);

private:
    // ECS
    entt::registry m_registry;

    // ECS системы
    std::unique_ptr<MovementSystem> m_movementSystem;
    std::unique_ptr<RendererSystem> m_renderSystem;
    std::unique_ptr<CombatSystem> m_combatSystem;
    std::unique_ptr<AnimationSystem> m_animationSystem;
    std::unique_ptr<CleanupSystem> m_cleanupSystem;
    void initGameObjects();
};
