#include "Time.h"
#include <GLFW/glfw3.h>

float Time::s_deltaTime = 0.0f;
float Time::s_currentTime = 0.0f;
float Time::s_lastFrame = 0.0f;
float Time::s_fps = 0.0f;
int Time::s_frameCount = 0;
float Time::s_lastFPSUpdate = 0.0f;
float Time::s_timeScale = 1.0f;

void Time::update() {
    s_currentTime = static_cast<float>(glfwGetTime());
    s_deltaTime = (s_currentTime - s_lastFrame) * s_timeScale;
    if (s_deltaTime > 0.05f) {
        s_deltaTime = 0.05f; // Защита от "туннелирования" (прохождения сквозь стены) при лагах или перетаскивании окна
    }
    s_lastFrame = s_currentTime;

    // FPS counter
    s_frameCount++;
    if (s_currentTime - s_lastFPSUpdate >= 0.5f) {
        s_fps = s_frameCount / (s_currentTime - s_lastFPSUpdate);
        s_frameCount = 0;
        s_lastFPSUpdate = s_currentTime;
    }
}