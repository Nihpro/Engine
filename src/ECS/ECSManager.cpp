#include "ECSManager.h"
#include "../Input/KeyCodes.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/Renderer.h"


ECSManager::ECSManager() = default;

void ECSManager::init() {
    m_movementSystem = std::make_unique<MovementSystem>();
    m_renderSystem = std::make_unique<RendererSystem>();
    m_animationSystem = std::make_unique<AnimationSystem>();

    initGameObjects();
}

void ECSManager::update(float deltaTime) {
    m_movementSystem->update(m_registry, deltaTime);
    m_animationSystem->update(m_registry, deltaTime);
}

void ECSManager::processInput() {
    auto view = m_registry.view<PlayerTag, Velocity>();
    for (auto [entity, vel] : view.each()) {
        vel.value = glm::vec2(0.0f);

        if (KeyCode::isPressed("W")) vel.value.y = 200.0f;
        if (KeyCode::isPressed("S")) vel.value.y = -200.0f;
        if (KeyCode::isPressed("A")) vel.value.x = -200.0f;
        if (KeyCode::isPressed("D")) vel.value.x = 200.0f;
    }
}



void ECSManager::render(Renderer* render) {
    m_renderSystem->update(m_registry, render);
}

glm::vec2 ECSManager::getPlayerPosition() {
    auto view = m_registry.view<PlayerTag>();

    
    if (view.begin() == view.end()) {
        return glm::vec2(0.0f);
    }

    // Берём первую сущность с PlayerTag
    entt::entity player = *view.begin();

    // Получаем позицию
    return m_registry.get<Position>(player).value;
}

void ECSManager::initGameObjects() {
    


    auto blockSprite = ResourceManager::getSprite("Box");
    for (int i = 0; i < 10; i++)
    {
        
        auto block = m_registry.create();
        m_registry.emplace<Position>(block, 0.f, i*64.f);
        m_registry.emplace<Renderable>(block, blockSprite, glm::vec2(64.0f, 64.0f));
        m_registry.get<Renderable>(block).layer = 100;
    }
    auto playerSprite = ResourceManager::getSprite("Box");

    auto player = m_registry.create();
    m_registry.emplace<Position>(player, 400.0f, 300.0f);
    m_registry.emplace<Velocity>(player, 0.0f, 0.0f);
    m_registry.emplace<Health>(player, 100, 100);
    m_registry.emplace<Player>(player);
    m_registry.emplace<PlayerTag>(player);
    m_registry.emplace<Renderable>(player, playerSprite, glm::vec2(64.0f, 64.0f));
    m_registry.get<Renderable>(player).layer = 20;
}