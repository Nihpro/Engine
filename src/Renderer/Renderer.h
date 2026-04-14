#pragma once
#include "OpenGL.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Shader;
class Camera;
class Texture2D;
class Sprite;

struct QuadVertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void beginDraw(Camera* camera, float screenWidth, float screenHeight);
    void endDraw();

    
    void draw(const glm::vec2& position, const glm::vec2& size,
        std::shared_ptr<Texture2D> texture = nullptr, float rotation = 0.0f,
        const glm::vec3& color = glm::vec3(1.0f));

    void draw(const glm::mat4& transform, std::shared_ptr<Texture2D> texture = nullptr,
        const glm::vec3& color = glm::vec3(1.0f));

    void draw(const glm::vec2& position, const glm::vec2& size,
        std::shared_ptr<Sprite> sprite,
        float rotation = 0.0f,
        const glm::vec3& color = glm::vec3(1.0f));

    void draw(const glm::mat4& transform,
        std::shared_ptr<Sprite> sprite,
        const glm::vec3& color = glm::vec3(1.0f));

    void setClearColor(float r, float g, float b, float a);

private:
    void uploadToGPU();

    GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;
    std::shared_ptr<Shader> m_shader;
    std::vector<QuadVertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::shared_ptr<Texture2D> m_currentTexture = nullptr;
    glm::mat4 m_projection;
    glm::mat4 m_view;

    static constexpr size_t MAX_VERTICES = 10000;
    static constexpr size_t MAX_INDICES = 15000;
};