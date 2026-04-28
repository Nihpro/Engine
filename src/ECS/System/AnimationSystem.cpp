#include "AnimationSystem.h"
#include "../Components/Animation.h"
#include "../Components/Render.h"
#include "../../Renderer/SpriteAnimator.h"

void AnimationSystem::update(entt::registry& registry, float deltaTime) {
    auto view = registry.view<Animation, Renderable>();

    for (auto [entity, anim, render] : view.each()) {
        if (!anim.playing || !anim.animator) continue;

        anim.animator->update(deltaTime);
        render.currentFrame = anim.animator->getCurrentFrame();
    }
}