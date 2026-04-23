#pragma once
#include <memory>
#include <filesystem> 

#include <entt.hpp>
#include "../ECS/ECSManager.h"

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

    // ECS
    std::unique_ptr<ECSManager> m_ecsManager;

    bool m_running = true;
    bool m_cursorDisabled = true;
    bool m_altPressed = false;
    bool m_vSyncEnabled = true;


    
};