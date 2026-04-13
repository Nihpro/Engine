#include "AnimationSystem.h"
#include "../Components/Animation.h"
#include "../Components/Render.h"

void AnimationSystem::update(entt::registry& registry, float deltaTime) {
    auto view = registry.view<Animation, Renderable>();

    for (auto [entity, anim, render] : view.each()) {
        if (!anim.playing || anim.frames.empty()) continue;

        anim.currentTime += deltaTime;

        if (anim.currentTime >= anim.frameDuration) {
            anim.currentTime = 0.0f;
            anim.currentFrame++;

            if (anim.currentFrame >= anim.frames.size()) {
                if (anim.loop) {
                    anim.currentFrame = 0;
                }
                else {
                    anim.currentFrame = static_cast<int>(anim.frames.size()) - 1;
                    anim.playing = false;
                }
            }

            // Меняем спрайт на текущий кадр
            render.sprite = anim.frames[anim.currentFrame];
        }
    }
}