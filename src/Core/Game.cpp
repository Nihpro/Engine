#include "Game.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include "../System/Window.h"     
#include "../System/Time.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Texture2D.h"
#include "../Input/InputManager.h"
#include "../Input/CameraController.h"
#include "../Camera/Camera.h"
#include "../Renderer/Sprite.h"
#include "../Resources/ResourceManager.h"

#include <filesystem>
#include <iostream>

Game::Game() {
    init();
}

Game::~Game() {
    cleanup();
}

//Выполняется только 1 раз при запуске
void Game::init() {

    
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return;
    }

    // Создаём окно
    m_window = std::make_unique<Window>(800, 600, "2D Engine");
    if (!m_window->getNativeWindow()) {
        std::cout << "Failed to create window\n";
        return;
    }

    // Инициализируем GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }

    // Настройки OpenGL
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Переключатель вертикальной синхронизации
    m_window->setVSync(m_vSyncEnabled);

    // Инициализируем InputManager
    InputManager::init(m_window->getNativeWindow());
    InputManager::setCursorMode(true);

    // Создаём камеру и контроллер
    m_camera = std::make_unique<Camera>(glm::vec2(0.0f), 500.0f, 1.0f);
    m_cameraController = std::make_unique<CameraController>(m_camera.get());

    //Загрузка ресурсов
    ResourceManager::loadJSONResources("res/resources.json");

    // Создаём рендерер
    m_renderer = std::make_unique<Renderer>();
    m_renderer->init();

    //Инициализация Объектов ECS
    m_movementSystem = std::make_unique<MovementSystem>();
    m_renderSystem = std::make_unique<RendererSystem>();
    m_combatSystem = std::make_unique<CombatSystem>();
    m_animationSystem = std::make_unique<AnimationSystem>();
    m_cleanupSystem = std::make_unique<CleanupSystem>();

    // Создание игровых объектов
    initGameObjects();
}

//Игровой цикл
void Game::run() {
    while (m_running && !m_window->shouldClose()) {
        Time::update();

        processInput();

        update(Time::getDeltaTime());

        render();

        m_window->swapBuffers();
        m_window->pollEvents();

        // Обновляем заголовок окна с FPS
        m_window->setTitle("2D Engine - FPS: " + std::to_string(static_cast<int>(Time::getFPS())));
    }
}

void Game::processInput() {
    InputManager::update();

    // Выход по Escape
    if (InputManager::isKeyPressed(GLFW_KEY_ESCAPE)) {
        m_window->setShouldClose(true);
    }

    // Переключение каркасного режима (F3)
    static bool wireframePressed = false;
    if (InputManager::isKeyJustPressed(GLFW_KEY_F3)) {
        static bool wireframe = false;
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }

    // Переключение курсора (ALT)
    if (InputManager::isKeyJustPressed(GLFW_KEY_LEFT_ALT)) {
        m_cursorDisabled = !m_cursorDisabled;
        InputManager::setCursorMode(m_cursorDisabled);
    }

    // Переключение VSync (V)
    if (InputManager::isKeyJustPressed(GLFW_KEY_V)) {
        m_vSyncEnabled = !m_vSyncEnabled;
        m_window->setVSync(m_vSyncEnabled);
    }

    // Управление камерой
    /*if (m_cameraController) {
        m_cameraController->onUpdate(Time::getDeltaTime());
    }*/

    // Обработка движения мыши для поворота камеры
    /*float mouseDx, mouseDy;
    InputManager::getMouseDelta(mouseDx, mouseDy);
    if (m_cameraController) {
        m_cameraController->onMouseMove(mouseDx, mouseDy);
    }*/

    // Управление игроком через ECS
    auto view = m_registry.view<PlayerTag, Velocity>();
    for (auto [entity, vel] : view.each()) {
        vel.value = glm::vec2(0.0f);

        if (InputManager::isKeyPressed(GLFW_KEY_W)) vel.value.y = 200.0f;
        if (InputManager::isKeyPressed(GLFW_KEY_S)) vel.value.y = -200.0f;
        if (InputManager::isKeyPressed(GLFW_KEY_A)) vel.value.x = -200.0f;
        if (InputManager::isKeyPressed(GLFW_KEY_D)) vel.value.x = 200.0f;
    }


}

void Game::update(float deltaTime) {
    // Обновляем ECS системы в правильном порядке
    m_movementSystem->update(m_registry, deltaTime);
    m_animationSystem->update(m_registry, deltaTime);
    m_combatSystem->update(m_registry);
    m_cleanupSystem->update(m_registry);
}

void Game::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    static int renderFrame = 0;
    if (renderFrame++ % 60 == 0) {
        std::cout << "Game::render frame " << renderFrame << std::endl;
        std::cout << "Camera position: (" << m_camera->Position.x << ", " << m_camera->Position.y << ")" << std::endl;
        std::cout << "Window size: " << m_window->getWidth() << "x" << m_window->getHeight() << std::endl;
    }

    if (m_renderer && m_camera) {
        m_renderer->beginDraw(m_camera.get(), static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()));
        
        // Рендерим ECS объекты
        m_renderSystem->update(m_registry, m_renderer.get());

        m_renderer->endDraw();
    }
}

void Game::cleanup() {
    m_renderer.reset();
    m_cameraController.reset();
    m_camera.reset();
    m_window.reset();

    ResourceManager::unloadAllResources();


    glfwTerminate();
}

void Game::initGameObjects()
{
    auto blockSprite = ResourceManager::getSprite("Box");

    auto block = m_registry.create();
    m_registry.emplace<Position>(block, 400.0f, 300.0f);
    m_registry.emplace<Velocity>(block, 0.0f, 0.0f);
    m_registry.emplace<Health>(block, 100, 100);
    m_registry.emplace<Player>(block);
    m_registry.emplace<PlayerTag>(block);
    m_registry.emplace<Renderable>(block, blockSprite, glm::vec2(64.0f, 64.0f));


}

void Game::shutdown() {
    m_running = false;
}