#include "Camera.h"

Camera::Camera(vec2 position, float speed, float zoom)
    : Position(position),
    MovementSpeed(speed),
    MouseSensitivity(SENSITIVITY),
    Zoom(zoom),
    Yaw(0.f)
{
    updateCameraVectors();
}

mat4 Camera::GetViewMatrix() {
    mat4 view = glm::mat4(1.0f);
    view = glm::rotate(view, glm::radians(-Yaw), glm::vec3(0, 0, 1));
    view = glm::translate(view, glm::vec3(-Position.x, -Position.y, 0.0f));
    return view;
}

mat4 Camera::GetProjectionMatrix(float width, float height) {
    float left = -width / 2.0f;
    float right = width / 2.0f;
    float bottom = -height / 2.0f;
    float top = height / 2.0f;

    return ortho(
        left / Zoom,
        right / Zoom,
        bottom / Zoom,
        top / Zoom,
        -1.0f,
        1.0f
    );
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = deltaTime * GetCurrentSpeed();

    switch (direction) {
    case FORWARD:  Position += Front * velocity; break;
    case BACKWARD: Position -= Front * velocity; break;
    case LEFT:     Position -= Right * velocity; break;
    case RIGHT:    Position += Right * velocity; break;
    case ROTATE_LEFT:  Yaw += 120.0f * deltaTime; break;
    case ROTATE_RIGHT: Yaw -= 120.0f * deltaTime; break;
    case BOOST:    IsBoosting = true; return;
    }

    if (direction == BOOST) {
        IsBoosting = true;
    }
    else {
        IsBoosting = false;
    }

    updateCameraVectors();
}

float Camera::GetCurrentSpeed() const {
    return IsBoosting ? MovementSpeed * Boost : MovementSpeed;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    // Для 2D обычно не нужен Pitch, только Yaw для вращения

    // Нормализация угла
    Yaw = fmod(Yaw, 360.0f);
    if (Yaw < 0) Yaw += 360.0f;

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom *= (yoffset > 0) ? 1.1f : 0.9f;
    Zoom = clamp(Zoom, 0.1f, 10.0f);
}

void Camera::updateCameraVectors() {
    float rad = glm::radians(Yaw);

    // Front = направление "вверх" (при Yaw = 0)
    Front = glm::normalize(vec2(-sin(rad), cos(rad)));

    // Right = направление "вправо" (перпендикулярно Front)
    Right = glm::normalize(vec2(cos(rad), sin(rad)));
}