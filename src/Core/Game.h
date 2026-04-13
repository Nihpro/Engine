#pragma once
#include <memory>
#include <filesystem> 

class Window;
class Renderer;
class Scene;
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
    std::unique_ptr<Scene> m_activeScene;

    bool m_running = true;
    bool m_cursorDisabled = true;
    bool m_altPressed = false;
    bool m_vSyncEnabled = true;
};