#include "PlayerControlSystem.h"

#include "../../Input/KeyCodes.h"
#include "../Components/Transform.h"
#include "../Components/Gameplay.h"

void PlayerControlSystem::processInput(entt::registry& registry)
{
    auto view = registry.view<PlayerTag, Velocity>();
    for (auto [entity, vel] : view.each()) {
        vel.value = glm::vec2(0.0f);

        if (KeyCode::isPressed("W")) vel.value.y = speed;
        if (KeyCode::isPressed("S")) vel.value.y = -speed;
        if (KeyCode::isPressed("A")) vel.value.x = -speed;
        if (KeyCode::isPressed("D")) vel.value.x = speed;

        //Нормализация для того чтобы при беге по диагонали скорость равнялясь 200
        if (glm::length(vel.value) > 0) {
            vel.value = glm::normalize(vel.value) * speed;
        }
    }
}
