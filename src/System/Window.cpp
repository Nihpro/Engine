#include "Window.h"
#include "../Renderer/OpenGL.h"    
#include <iostream>
#include "../Input/InputManager.h"

static Window* s_currentWindow = nullptr;
static bool s_glfwInitialized = false;

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr) {

    if (!s_glfwInitialized) {
        if (!glfwInit()) {
            std::cout << "Failed to initialize GLFW\n";
            return;
        }
        s_glfwInitialized = true;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cout << "Failed to create GLFW window\n";
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetCursorPosCallback(m_window, cursorPosCallback);
    glfwSetScrollCallback(m_window, scrollCallback);

    s_currentWindow = this;
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::setShouldClose(bool close) {
    glfwSetWindowShouldClose(m_window, close);
}

void Window::setVSync(bool enabled) {
    m_vSync = enabled;
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::setTitle(const std::string& title) {
    m_title = title;
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::setCursorMode(bool disabled) {
    glfwSetInputMode(m_window, GLFW_CURSOR, disabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

// ===== CALLBACK ФУНКЦИИ =====
void Window::framebufferCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    if (s_currentWindow) {
        s_currentWindow->m_width = width;
        s_currentWindow->m_height = height;
    }
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        InputManager::onKeyPressed(key);
    }
    else if (action == GLFW_RELEASE) {
        InputManager::onKeyReleased(key);
    }
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        InputManager::onMouseButtonPressed(button);
    }
    else if (action == GLFW_RELEASE) {
        InputManager::onMouseButtonReleased(button);
    }
}

void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    InputManager::onMouseMove(static_cast<float>(xpos), static_cast<float>(ypos));
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    InputManager::onScroll(static_cast<float>(yoffset));
}