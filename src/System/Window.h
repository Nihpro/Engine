#pragma once
#include <string>

struct GLFWwindow;

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void pollEvents();
    void swapBuffers();
    bool shouldClose() const;
    void setShouldClose(bool close);

    GLFWwindow* getNativeWindow() const { return m_window; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    void setVSync(bool enabled);
    void setTitle(const std::string& title);
    void setCursorMode(bool disabled);

private:
    static void framebufferCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow* m_window;
    int m_width, m_height;
    std::string m_title;
    bool m_vSync = true;
};