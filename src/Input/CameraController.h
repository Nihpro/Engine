#pragma once
#include "../Camera/Camera.h"

class CameraController {
public:
    CameraController(Camera* camera);

    void onUpdate(float deltaTime);
    void onMouseMove(float xoffset, float yoffset);
    void onScroll(float yoffset);

    void setSpeed(float speed) { m_speed = speed; }
    void setBoost(float boost) { m_boost = boost; }
    void setRotationSpeed(float speed) { m_rotationSpeed = speed; }

    Camera* getCamera() const { return m_camera; }

private:
    Camera* m_camera;
    float m_speed = 500.0f;
    float m_boost = 2.5f;
    float m_rotationSpeed = 120.0f;
    bool m_isBoosting = false;
};