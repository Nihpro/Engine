#pragma once 

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

enum CameraMovement {
    FORWARD,    // Вверх
    BACKWARD,   // Вниз
    LEFT,       // Влево
    RIGHT,      // Вправо
    ROTATE_LEFT,   // Поворот влево
    ROTATE_RIGHT,  // Поворот вправо
    BOOST       // Ускорение
};

// 2D параметры
const float SPEED = 500.0f;      // Пикселей в секунду
const float SENSITIVITY = 0.1f;
const float ZOOM = 1.0f;

class Camera
{
public:
    // 2D
    vec2 Position;           // Позиция в пикселях
    vec2 Front;              // Направление "вперёд"
    vec2 Right;              // Направление "вправо"

    float MovementSpeed;     // Скорость движения
    float MouseSensitivity;  // Чувствительность мыши
    float Zoom;              // Масштаб (1.0 = 100%)

    float Yaw;               // Угол поворота в градусах (для вращения камеры)
    bool IsBoosting = false;
    float Boost = 2.5f;

    // Конструкторы
    Camera(vec2 position = vec2(0.f, 0.f),
        float speed = SPEED,
        float zoom = ZOOM);

    // Матрицы
    mat4 GetViewMatrix();
    mat4 GetProjectionMatrix(float width, float height);

    // Управление
    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    float GetCurrentSpeed() const;
    void ProcessMouseMovement(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};