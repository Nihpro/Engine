#include "PlayerControlSystem.h"

#include "../../Input/KeyCodes.h"
#include "../Components/Transform.h"
#include "../Components/Gameplay.h"

void PlayerControlSystem::processInput(entt::registry& registry) {
    auto view = registry.view<PlayerTag, Velocity>();

    for (auto [entity, vel] : view.each()) {
        // 1. Собираем чистое направление (-1, 0 или 1 по каждой оси)
        glm::vec2 direction(0.0f);

        if (KeyCode::isPressed("W")) direction.y += 1.0f;
        if (KeyCode::isPressed("S")) direction.y -= 1.0f;
        if (KeyCode::isPressed("A")) direction.x -= 1.0f;
        if (KeyCode::isPressed("D")) direction.x += 1.0f;

        // 2. Нормализуем и применяем скорость
        if (glm::length(direction) > 0.0f) {
            // Нормализуем направление, чтобы по диагонали длина вектора была равна 1
            direction = glm::normalize(direction);
        }

        // 3. Записываем итоговую скорость
        vel.value = direction * maxSpeed;
    }
}
