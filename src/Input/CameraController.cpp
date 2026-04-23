#include "CameraController.h"
#include "InputManager.h"

CameraController::CameraController(Camera* camera)
    : m_camera(camera) {}

void CameraController::onUpdate(float deltaTime) {
    if (!m_camera) return;

    // Движение
    if (InputManager::isKeyPressed(GLFW_KEY_W))
        m_camera->ProcessKeyboard(FORWARD, deltaTime);
    if (InputManager::isKeyPressed(GLFW_KEY_S))
        m_camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (InputManager::isKeyPressed(GLFW_KEY_A))
        m_camera->ProcessKeyboard(LEFT, deltaTime);
    if (InputManager::isKeyPressed(GLFW_KEY_D))
        m_camera->ProcessKeyboard(RIGHT, deltaTime);

    // Поворот
    if (InputManager::isKeyPressed(GLFW_KEY_Q))
        m_camera->ProcessKeyboard(ROTATE_LEFT, deltaTime);
    if (InputManager::isKeyPressed(GLFW_KEY_E))
        m_camera->ProcessKeyboard(ROTATE_RIGHT, deltaTime);

    // Ускорение
    m_isBoosting = InputManager::isKeyPressed(GLFW_KEY_LEFT_SHIFT);
    if (m_isBoosting) {
        m_camera->ProcessKeyboard(BOOST, deltaTime);
    }
    // Обработка скролла для зума
    float scrollOffset = InputManager::getScrollOffset();
    if (scrollOffset != 0.0f && InputManager::isCursorDisabled()) {
        m_camera->ProcessMouseScroll(scrollOffset);
    }
}

void CameraController::onMouseMove(float xoffset, float yoffset) {
    if (m_camera && InputManager::isCursorDisabled()) {
        m_camera->ProcessMouseMovement(xoffset, yoffset);
    }
}


void CameraController::onScroll(float yoffset) {
    if (m_camera && InputManager::isCursorDisabled()) {
        m_camera->ProcessMouseScroll(yoffset);
    }
}

void CameraController::setPosition(vec2& pos)
{
    m_camera->SetPosition(pos);
}
