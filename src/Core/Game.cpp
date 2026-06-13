#include "Game.h"
#include "../Renderer/OpenGL.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../System/Window.h"     
#include "../System/Time.h"
#include "../Renderer/Texture2D.h"
#include "../Input/KeyCodes.h"
#include "../Input/CameraController.h"
#include "../Camera/Camera.h"
#include "../Renderer/Sprite.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <iostream>

Game::Game() {
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

    m_ecsManager = std::make_unique<ECSManager>();
    m_ecsManager->init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window->getNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

//Игровой цикл
void Game::run() {
    while (m_running && !m_window->shouldClose()) {
        Time::update();

        processInput();

        update(Time::getDeltaTime());

        render();

        m_window->swapBuffers();
        InputManager::update();
        m_window->pollEvents();

        // Обновляем заголовок окна с FPS
        m_window->setTitle("2D Engine - FPS: " + std::to_string(static_cast<int>(Time::getFPS())));
    }
}

void Game::processInput() {
    

    // Выход по Escape
    if (KeyCode::isPressed("ESCAPE")) {
        m_window->setShouldClose(true);
    }

    // Переключение каркасного режима (F3)
    static bool wireframePressed = false;
    if (KeyCode::isJustPressed("F3")) {
        static bool wireframe = false;
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    }

    // Переключение курсора (ALT)
    if (KeyCode::isJustPressed("LEFT_ALT")) {
        m_cursorDisabled = !m_cursorDisabled;
        InputManager::setCursorMode(m_cursorDisabled);
    }

    // Переключение VSync (V)
    if (KeyCode::isJustPressed("V")) {
        m_vSyncEnabled = !m_vSyncEnabled;
        m_window->setVSync(m_vSyncEnabled);
    }



    // Управление камерой
    if (m_cameraController) {
        m_cameraController->onUpdate(Time::getDeltaTime());
    }

    if (!KeyCode::isPressed("LEFT_CONTROL")) {
        m_cameraController->setPosition(m_ecsManager->getPlayerPosition());
    }
    else {
        // Обработка движения мыши для поворота камеры
        float mouseDx, mouseDy;
        InputManager::getMouseDelta(mouseDx, mouseDy);
        if (m_cameraController) {
            m_cameraController->onMouseMove(mouseDx, mouseDy);
        }
    }


    
    

    //Контроллер ECS
    if(m_cursorDisabled)
    {
        m_ecsManager->processInput();
    }
    


}

void Game::update(float deltaTime) {
    //Обновляем обьекты ECS
    m_ecsManager->update(deltaTime);



    //glm::vec2 playerPos = m_ecsManager->getPlayerPosition();
    //m_camera->SetPosition(playerPos);
    

   
   
}

void Game::render() {
    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    static int renderFrame = 0;
    if (renderFrame++ % 60 == 0) {
        std::cout << "Game::render frame " << renderFrame << std::endl;
        std::cout << "Camera position: (" << m_camera->Position.x << ", " << m_camera->Position.y << ")" << std::endl;
        std::cout << "Window size: " << m_window->getWidth() << "x" << m_window->getHeight() << std::endl;
    }
    if (m_camera) {
        glm::mat4 projectionMatrix = m_camera->GetProjectionMatrix(static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()));
        glm::mat4 viewMatrix = m_camera->GetViewMatrix();
        
        const char* shadersToUpdate[] = { "Default", "AlphaMask" };
        for (const char* shaderName : shadersToUpdate) {
            auto pSpriteShader = ResourceManager::getShaderProgram(shaderName);
            if (pSpriteShader) {
                pSpriteShader->use();
                pSpriteShader->setMatrix4("projectionMat", projectionMatrix);
                pSpriteShader->setMatrix4("viewMat", viewMatrix);
            }
        }

        // Рендерим ECS объекты
        m_ecsManager->render();
    }
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug Menu");


    ImGui::Text("FPS: %.1f", Time::getFPS());
    glm::vec2 playerPos = m_ecsManager->getPlayerPosition();
    if (m_camera) {
        ImGui::Text("Camera Pos: X: %.2f, Y: %.2f", m_camera->Position.x, m_camera->Position.y);
        ImGui::Text("Player Pos: X: %.2f, Y: %.2f", playerPos.x, playerPos.y);
    }
    ImGui::ColorEdit4("Bockground Color:", glm::value_ptr(m_backgroundColor));

    


    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    
}

void Game::cleanup() {
    m_cameraController.reset();
    m_camera.reset();
    m_window.reset();

    ResourceManager::unloadAllResources();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}



void Game::shutdown() {
    m_running = false;
}