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
    // Сохраняем предыдущее состояние
    s_previousKeys = s_currentKeys;
    s_previousMouse = s_currentMouse;

    // Обновляем дельту мыши
    s_mouseDeltaX = 0.0f;
    s_mouseDeltaY = 0.0f;
}

// ===== СОБЫТИЙНЫЕ МЕТОДЫ =====
void InputManager::onKeyPressed(int keycode) {
    s_currentKeys[keycode] = true;
}

void InputManager::onKeyReleased(int keycode) {
    s_currentKeys[keycode] = false;
}

void InputManager::onMouseButtonPressed(int button) {
    s_currentMouse[button] = true;
}

void InputManager::onMouseButtonReleased(int button) {
    s_currentMouse[button] = false;
}

void InputManager::onMouseMove(float x, float y) {
    if (s_firstMouse) {
        s_lastMouseX = x;
        s_lastMouseY = y;
        s_firstMouse = false;
    }

    s_mouseDeltaX = x - s_lastMouseX;
    s_mouseDeltaY = s_lastMouseY - y;
    s_lastMouseX = x;
    s_lastMouseY = y;
}

void InputManager::onScroll(float yoffset) {
    s_scrollOffset = yoffset;
}

// ===== МЕТОДЫ ДЛЯ ПРОВЕРКИ СОСТОЯНИЯ =====
//Зажатие кнопки
bool InputManager::isKeyPressed(int keycode) {
    return s_currentKeys[keycode];
}

//Нажатие кнопки
bool InputManager::isKeyJustPressed(int keycode) {
    return s_currentKeys[keycode] && !s_previousKeys[keycode];
}

//Отжатие кнопки
bool InputManager::isKeyReleased(int keycode) {
    return !s_currentKeys[keycode] && s_previousKeys[keycode];
}

//Зажатие кнопки мыши
bool InputManager::isMouseButtonPressed(int button) {
    return s_currentMouse[button];
}
//Нажатие кнопки мыши
bool InputManager::isMouseButtonJustPressed(int button) {
    return s_currentMouse[button] && !s_previousMouse[button];
}
//Отжатие кнопки мыши
bool InputManager::isMouseButtonReleased(int button) {
    return !s_currentMouse[button] && s_previousMouse[button];
}

//Возращает текущую позицию курсора
void InputManager::getMousePosition(float& x, float& y) {
    x = s_lastMouseX;
    y = s_lastMouseY;
}

void InputManager::getMouseDelta(float& dx, float& dy) {
    dx = s_mouseDeltaX;
    dy = s_mouseDeltaY;
    s_mouseDeltaX = 0.0f;
    s_mouseDeltaY = 0.0f;
}

//Активный курсор или нет
void InputManager::setCursorMode(bool disabled) {
    s_cursorDisabled = disabled;
    glfwSetInputMode(s_window, GLFW_CURSOR, disabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    s_firstMouse = true;
}

//Говорит в каком режиме курсор
bool InputManager::isCursorDisabled() {
    return s_cursorDisabled;
}

//Возращает значение скрола
float InputManager::getScrollOffset() {
    float offset = s_scrollOffset;
    s_scrollOffset = 0.0f;
    return offset;
}