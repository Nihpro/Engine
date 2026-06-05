#pragma once
#include <glm/glm.hpp>

struct Position {
    glm::vec2 value = glm::vec2(0.0f);

    Position() = default;
    Position(float x, float y) : value(x, y) {}
    Position(const glm::vec2& pos) : value(pos) {}
};

struct Velocity {
    glm::vec2 value = glm::vec2(0.0f);

    Velocity() = default;
    Velocity(float vx, float vy) : value(vx, vy) {}
    Velocity(const glm::vec2& vel) : value(vel) {}
    bool operator!=(const Velocity& vel)const {
        return (value.x != vel.value.x && value.y != vel.value.y);
    }
};

struct Rotation {
    float angle = 0.0f;  // в градусах
};

struct Scale {
    glm::vec2 value = glm::vec2(1.0f);
};