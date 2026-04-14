#include "ECSManager.h"
#include "../Input/InputManager.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/Renderer.h"

// Коды клавиш (ASCII)
namespace Key {
    constexpr int W = 87;
    constexpr int S = 83;
    constexpr int A = 65;
    constexpr int D = 68;
}

ECSManager::ECSManager() = default;

void ECSManager::init() {
    m_movementSystem = std::make_unique<MovementSystem>();
    m_renderSystem = std::make_unique<RendererSystem>();
    m_combatSystem = std::make_unique<CombatSystem>();
    m_animationSystem = std::make_unique<AnimationSystem>();
    m_cleanupSystem = std::make_unique<CleanupSystem>();

    initGameObjects();
}

void ECSManager::processInput() {
    auto view = m_registry.view<PlayerTag, Velocity>();
    for (auto [entity, vel] : view.each()) {
        vel.value = glm::vec2(0.0f);

        if (InputManager::isKeyPressed(Key::W)) vel.value.y = 200.0f;
        if (InputManager::isKeyPressed(Key::S)) vel.value.y = -200.0f;
        if (InputManager::isKeyPressed(Key::A)) vel.value.x = -200.0f;
        if (InputManager::isKeyPressed(Key::D)) vel.value.x = 200.0f;
    }
}

void ECSManager::update(float deltaTime) {
    m_movementSystem->update(m_registry, deltaTime);
    m_animationSystem->update(m_registry, deltaTime);
    m_combatSystem->update(m_registry);
    m_cleanupSystem->update(m_registry);
}

void ECSManager::render(Renderer* render) {
    m_renderSystem->update(m_registry, render);
}

void ECSManager::initGameObjects() {
    auto blockSprite = ResourceManager::getSprite("Box");

    auto block = m_registry.create();
    m_registry.emplace<Position>(block, 400.0f, 300.0f);
    m_registry.emplace<Velocity>(block, 0.0f, 0.0f);
    m_registry.emplace<Health>(block, 100, 100);
    m_registry.emplace<Player>(block);
    m_registry.emplace<PlayerTag>(block);
    m_registry.emplace<Renderable>(block, blockSprite, glm::vec2(64.0f, 64.0f));
}