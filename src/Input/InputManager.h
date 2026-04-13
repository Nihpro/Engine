#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputManager {
public:
    static void init(GLFWwindow* window);
    static void update();

    static bool isKeyPressed(int keycode);
    static bool isKeyJustPressed(int keycode);
    static bool isKeyReleased(int keycode);

    static bool isMouseButtonPressed(int button);
    static bool isMouseButtonJustPressed(int button);

    static void getMousePosition(float& x, float& y);
    static void getMouseDelta(float& dx, float& dy);

    static void setCursorMode(bool disabled);
    static bool isCursorDisabled();

    static void onScroll(float yoffset);

    static float getScrollOffset();

private:
    static GLFWwindow* s_window;
    static std::unordered_map<int, bool> s_currentKeys;
    static std::unordered_map<int, bool> s_previousKeys;
    static std::unordered_map<int, bool> s_currentMouse;
    static std::unordered_map<int, bool> s_previousMouse;
    static bool s_cursorDisabled;
    static float s_lastMouseX, s_lastMouseY;
    static float s_mouseDeltaX, s_mouseDeltaY;
    static float s_scrollOffset;
    static bool s_firstMouse;
};