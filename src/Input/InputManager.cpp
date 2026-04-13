#include "InputManager.h"

GLFWwindow* InputManager::s_window = nullptr;
std::unordered_map<int, bool> InputManager::s_currentKeys;
std::unordered_map<int, bool> InputManager::s_previousKeys;
std::unordered_map<int, bool> InputManager::s_currentMouse;
std::unordered_map<int, bool> InputManager::s_previousMouse;
bool InputManager::s_cursorDisabled = true;
float InputManager::s_lastMouseX = 0.0f;
float InputManager::s_lastMouseY = 0.0f;
float InputManager::s_mouseDeltaX = 0.0f;
float InputManager::s_mouseDeltaY = 0.0f;
float InputManager::s_scrollOffset = 0.0f;
bool InputManager::s_firstMouse = true;

void InputManager::init(GLFWwindow* window) {
    s_window = window;
}

void InputManager::update() {
    s_previousKeys = s_currentKeys;
    s_previousMouse = s_currentMouse;

    // Обновляем состояние клавиш
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
        s_currentKeys[key] = glfwGetKey(s_window, key) == GLFW_PRESS;
    }

    // Обновляем состояние мыши
    for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button) {
        s_currentMouse[button] = glfwGetMouseButton(s_window, button) == GLFW_PRESS;
    }

    // Обновляем дельту мыши
    double x, y;
    glfwGetCursorPos(s_window, &x, &y);

    if (s_firstMouse) {
        s_lastMouseX = static_cast<float>(x);
        s_lastMouseY = static_cast<float>(y);
        s_firstMouse = false;
    }

    s_mouseDeltaX = static_cast<float>(x) - s_lastMouseX;
    s_mouseDeltaY = s_lastMouseY - static_cast<float>(y); // Реверсируем Y

    s_lastMouseX = static_cast<float>(x);
    s_lastMouseY = static_cast<float>(y);
}

bool InputManager::isKeyPressed(int keycode) {
    return s_currentKeys[keycode];
}

bool InputManager::isKeyJustPressed(int keycode) {
    return s_currentKeys[keycode] && !s_previousKeys[keycode];
}

bool InputManager::isKeyReleased(int keycode) {
    return !s_currentKeys[keycode] && s_previousKeys[keycode];
}

bool InputManager::isMouseButtonPressed(int button) {
    return s_currentMouse[button];
}

bool InputManager::isMouseButtonJustPressed(int button) {
    return s_currentMouse[button] && !s_previousMouse[button];
}

void InputManager::getMousePosition(float& x, float& y) {
    double dx, dy;
    glfwGetCursorPos(s_window, &dx, &dy);
    x = static_cast<float>(dx);
    y = static_cast<float>(dy);
}

void InputManager::getMouseDelta(float& dx, float& dy) {
    dx = s_mouseDeltaX;
    dy = s_mouseDeltaY;
    s_mouseDeltaX = 0.0f;
    s_mouseDeltaY = 0.0f;
}

void InputManager::setCursorMode(bool disabled) {
    s_cursorDisabled = disabled;
    glfwSetInputMode(s_window, GLFW_CURSOR, disabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    s_firstMouse = true;
}

bool InputManager::isCursorDisabled() {
    return s_cursorDisabled;
}

void InputManager::onScroll(float yoffset)
{
    s_scrollOffset = yoffset;
}

float InputManager::getScrollOffset()
{
    float offset = s_scrollOffset;
    s_scrollOffset = 0.0f;

    return offset;
}