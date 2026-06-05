#include "PlayerControlSystem.h"

#include "../../Input/KeyCodes.h"
#include "../Components/Transform.h"
#include "../Components/Gameplay.h"
#include "../Components/Physics.h"
#include <iostream>

void PlayerControlSystem::processInput(entt::registry& registry, float deltaTime)
{
    auto view = registry.view<PlayerTag, Velocity>();
    
    for (auto [entity, vel] : view.each()) {
        auto &ph = registry.get<PhysicsBody>(entity);

        if (KeyCode::isPressed("A")) vel.value.x -= acceleration * deltaTime;
        if (KeyCode::isPressed("D")) vel.value.x += acceleration * deltaTime;

        if (KeyCode::isJustPressed("SPACE"))
        {
            if(!ph.useGravity)
            {
                vel.value.y += 300.f;
                ph.useGravity = true;
                
            }
            
            std::cout << "Jump!" << ph.useGravity << " \n";
        }


        if (vel.value.x > maxSpeed) vel.value.x = maxSpeed;
        if (vel.value.x < -maxSpeed) vel.value.x = -maxSpeed;


        
    }
}
