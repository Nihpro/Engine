#include "ECSManager.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/SpriteAnimator.h"
#include "../ECS/Components/Animation.h"

#include <iostream>


ECSManager::ECSManager() = default;

void ECSManager::init() {
    m_movementSystem = std::make_unique<MovementSystem>();
    m_renderSystem = std::make_unique<RendererSystem>();
    m_animationSystem = std::make_unique<AnimationSystem>();
    m_playerControlSystem = std::make_unique<PlayerControlSystem>();
    m_collisionSystem = std::make_unique<CollisionSystem>();
    m_physicsSystem = std::make_unique<PhysicsSystem>();

    initGameObjects();
}

void ECSManager::update(float deltaTime) {
    m_playerControlSystem->processInput(m_registry, deltaTime);
    m_physicsSystem->update(m_registry, deltaTime);
    m_movementSystem->update(m_registry, deltaTime);
    m_collisionSystem->update(m_registry, deltaTime);
    m_animationSystem->update(m_registry, deltaTime);
}

void ECSManager::processInput() {
    
    
}



void ECSManager::render() {
    m_renderSystem->update(m_registry);
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
        string name = "Box" + std::to_string(i);
        std::cout << name << std::endl;
        m_registry.emplace<Info>(block, name);
        m_registry.emplace<Position>(block, i * 64.f, i % 2 == 0 ? 0.f : 64.f);
        m_registry.emplace<BoxCollider>(block, BoxCollider{ {false}, glm::vec2(64.0f, 64.0f) });
        m_registry.emplace<Renderable>(block, blockSprite, glm::vec2(64.0f, 64.0f));
        m_registry.get<Renderable>(block).layer = 0;
       
    }
    


    auto playerSprite = ResourceManager::getSprite("Circle"); // Измените на спрайт с анимацией, если есть

    auto player = m_registry.create();
    m_registry.emplace<Info>(player, "Player");
    m_registry.emplace<PlayerTag>(player);
    m_registry.emplace<Position>(player, 400.0f, 300.0f);
    m_registry.emplace<Velocity>(player, 0.0f, 0.0f);
    m_registry.emplace<Health>(player, 100, 100);
    m_registry.emplace<Player>(player);
    m_registry.emplace<Renderable>(player, playerSprite, glm::vec2(50.0f, 50.0f));
    m_registry.emplace<CircleCollider>(player, CircleCollider{ {false}, 25.f });
    m_registry.emplace<PointCollider>(player, PointCollider{{}});
    m_registry.emplace<PhysicsBody>(player, 1.f, .2f);

    m_registry.get<PointCollider>(player).offset = glm::vec2(0.f, -26.f);
    m_registry.get<Renderable>(player).layer = 20;

    

    /*if (playerSprite) {
        auto animator = std::make_shared<RenderEngine::SpriteAnimator>(playerSprite);
        m_registry.emplace<Animation>(player, animator, true);
    }*/
}