#include "Game.h"
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include "System/Window.h"     
#include "System/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture2D.h"
#include "Input/InputManager.h"
#include "Input/CameraController.h"
#include "Camera/Camera.h"
#include "Core/Scene.h"
#include "Core/GameObjects/GameObject.h"
#include "Renderer/Sprite.h"
#include "Resources/ResourceManager.h"

#include <filesystem>
#include <iostream>


class TestObject : public GameObject {
public:
    TestObject(const std::string& name, std::shared_ptr<Sprite> sprite, glm::vec2 pos)
        : GameObject(name), m_sprite(sprite){
        
        setPosition(pos);
        setScale(glm::vec2(100.0f, 100.0f));
        m_sprite->setColor(glm::vec3(1.0f, 1.0f, 1.0f));  // Белый цвет
    }

    void render(Renderer& renderer) override {
        renderer.drawQuad(getPosition(), getScale(), m_sprite->getTexture(), getRotation(), m_sprite->getColor());
    }

private:
    std::shared_ptr <Sprite> m_sprite;
};



Game::Game() {
    init();
}

Game::~Game() {
    cleanup();
}

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

    // Создаём сцену
    m_activeScene = std::make_unique<Scene>();

    // Загрузка текстуры
    

    auto sprite = ResourceManager::getSprite("Box");


    // Создание тестовых объектов
    auto obj1 = std::make_unique<TestObject>("Box1", sprite, glm::vec2(0.0f, 0.0f));
    obj1->setScale(glm::vec2(150.0f, 150.0f));

    auto obj2 = std::make_unique<TestObject>("Box2", sprite, glm::vec2(200.0f, 150.0f));
    obj2->setScale(glm::vec2(150.0f, 150.0f));
    obj2->setRotation(45.0f);

    auto obj3 = std::make_unique<TestObject>("Box3", sprite, glm::vec2(-200.0f, -150.0f));
    obj3->setScale(glm::vec2(150.0f, 150.0f));

    m_activeScene->addGameObject(std::move(obj1));
    m_activeScene->addGameObject(std::move(obj2));
    m_activeScene->addGameObject(std::move(obj3));


    m_activeScene->start();
    std::cout << "Test scene initialized with 3 objects!\n";

}

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
    if (m_cameraController) {
        m_cameraController->onUpdate(Time::getDeltaTime());
    }

    // Обработка движения мыши для поворота камеры
    /*float mouseDx, mouseDy;
    InputManager::getMouseDelta(mouseDx, mouseDy);
    if (m_cameraController) {
        m_cameraController->onMouseMove(mouseDx, mouseDy);
    }*/
}

void Game::update(float deltaTime) {
    if (m_activeScene) {
        m_activeScene->update(deltaTime);
    }
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

    if (m_renderer && m_activeScene && m_camera) {
        m_renderer->beginScene(m_camera.get(), static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()));
        m_activeScene->render(*m_renderer);
        m_renderer->endScene();
    }
}

void Game::cleanup() {
    m_activeScene.reset();
    m_renderer.reset();
    m_cameraController.reset();
    m_camera.reset();
    m_window.reset();

    ResourceManager::unloadAllResources();


    glfwTerminate();
}

void Game::shutdown() {
    m_running = false;
}