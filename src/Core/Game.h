#pragma once
#include <memory>
#include <filesystem> 

#include <entt.hpp>
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/Gameplay.h"
#include "../ECS/Components/Render.h"
#include "../ECS/System/AnimationSystem.h"
#include "../ECS/System/CleanupSystem.h"
#include "../ECS/System/CombatSystem.h"
#include "../ECS/System/MovementSystem.h"
#include "../ECS/System/RendererSystem.h"

class Window;
class Renderer;
class Camera;
class CameraController;
class Texture2D;

class Game {
public:
    Game();
    ~Game();

    void run();
    void shutdown();


private:
    void init();
    void processInput();
    void update(float deltaTime);
    void render();
    void cleanup();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<CameraController> m_cameraController;

    bool m_running = true;
    bool m_cursorDisabled = true;
    bool m_altPressed = false;
    bool m_vSyncEnabled = true;


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