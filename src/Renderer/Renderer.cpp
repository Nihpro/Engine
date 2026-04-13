#include "Renderer.h"
#include "Shader.h"
#include "Camera/Camera.h"
#include "Texture2D.h"
#include "Core/Game.h"
#include "Resources/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Renderer::Renderer() {
    m_vertices.reserve(MAX_VERTICES);
    m_indices.reserve(MAX_INDICES);
}

Renderer::~Renderer() {
    if (m_VAO) {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }
}

void Renderer::init() {
    // Создаём шейдер
    m_shader = ResourceManager::loadShaders("defaultShader", "res/shaders/shader.vs", "res/shaders/shader.fs");

    if (!m_shader) {
        std::cout << "ERROR: Shader failed to load!" << std::endl;
    }
    else {
        std::cout << "Shader loaded successfully!" << std::endl;
    }

    // Создаём VAO, VBO, EBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDICES * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, position));
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, color));
    glEnableVertexAttribArray(1);

    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Renderer::beginScene(Camera* camera, float screenWidth, float screenHeight) {
    if (!camera) {
        std::cout << "ERROR: No camera in beginScene!" << std::endl;
        return;
    }

    static int frameCount = 0;
    if (frameCount++ % 60 == 0) {
        std::cout << "beginScene called, frame " << frameCount << std::endl;
    }

    m_projection = camera->GetProjectionMatrix(screenWidth, screenHeight);
    m_view = camera->GetViewMatrix();

    m_vertices.clear();
    m_indices.clear();
    m_currentTexture = nullptr;
}

void Renderer::endScene() {
    flush();
}

void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& size,
    std::shared_ptr<Texture2D> texture, float rotation, const glm::vec3& color) {

    // Создаём трансформацию
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(position, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(size, 1.0f));

    // Вызываем основной метод
    drawQuad(transform, texture, color);
}

void Renderer::drawQuad(const glm::mat4& transform, std::shared_ptr<Texture2D> texture, const glm::vec3& color) {
    // Если текстура изменилась, сбрасываем текущий батч
    if (m_currentTexture != texture) {
        flush();
        m_currentTexture = texture;
    }

    // Проверяем, не переполнен ли буфер
    if (m_vertices.size() + 4 >= MAX_VERTICES || m_indices.size() + 6 >= MAX_INDICES) {
        flush();
    }

    // Вершины квада в локальном пространстве (-0.5, -0.5) -> (0.5, 0.5)
    glm::vec3 localVertices[4] = {
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f,  0.5f, 0.0f),
        glm::vec3(0.5f,  0.5f, 0.0f)
    };

    glm::vec2 texCoords[4] = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f)
    };

    size_t baseIndex = m_vertices.size();

    for (int i = 0; i < 4; ++i) {
        glm::vec4 worldPos = transform * glm::vec4(localVertices[i], 1.0f);
        m_vertices.push_back({ glm::vec3(worldPos), color, texCoords[i] });
    }

    // Индексы для двух треугольников
    m_indices.push_back(static_cast<GLuint>(baseIndex));
    m_indices.push_back(static_cast<GLuint>(baseIndex + 1));
    m_indices.push_back(static_cast<GLuint>(baseIndex + 2));
    m_indices.push_back(static_cast<GLuint>(baseIndex + 1));
    m_indices.push_back(static_cast<GLuint>(baseIndex + 3));
    m_indices.push_back(static_cast<GLuint>(baseIndex + 2));
}

void Renderer::flush() {
    if (m_vertices.empty()) {
        return;
    }

    static int flushCount = 0;
    if (flushCount++ % 60 == 0) {
        std::cout << "flush: drawing " << m_vertices.size() << " vertices, " << m_indices.size() << " indices" << std::endl;
    }

    if (m_shader) {
        m_shader->use();
        m_shader->setMatrix4fv("projection", m_projection);
        m_shader->setMatrix4fv("view", m_view);
        m_shader->setMatrix4fv("model", glm::mat4(1.0f));  // 👈 ДОБАВИТЬ! Единичная матрица

        if (m_currentTexture) {
            m_currentTexture->bind();
            m_shader->setInt("texture1", 0);
        }
    }

    // Загружаем данные в буферы
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(QuadVertex), m_vertices.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(GLuint), m_indices.data());

    // Рисуем
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);

    // Очищаем для следующего батча
    m_vertices.clear();
    m_indices.clear();
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}