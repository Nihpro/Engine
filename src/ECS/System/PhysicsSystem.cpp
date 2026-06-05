#include "PhysicsSystem.h"
#include <cmath>
#include <iostream>


void PhysicsSystem::update(entt::registry &registry, float deltaTime) {

  auto view = registry.view<PhysicsBody, Velocity>();

  for (auto [entity, phy, vel] : view.each()) {

    if (phy.isKinematic)
      continue;

    float &y = vel.value.y;
    float &x = vel.value.x;

    if (phy.useGravity) {
      y -= phy.gravityScale * 980.f * deltaTime; // 9.8 * 100 (пикселей в метре)
    }

    float drag = 5.f;

    x -= x * drag * deltaTime;
    if (std::abs(x) < 0.01f) {
      x = 0.f;
    }

    //std::cout << vel.value.x << ", " << vel.value.y << std::endl;
  }
}
