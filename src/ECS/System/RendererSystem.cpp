#include "RendererSystem.h"
#include "../Components/Transform.h"
#include "../Components/Render.h"
#include "../../Renderer/Renderer.h"
#include "../../Renderer/Sprite.h"

void RendererSystem::update(entt::registry& registry, Renderer* renderer) {
    if (!renderer) return;

    auto view = registry.view<Position, Renderable>();

    for (auto [entity, pos, render] : view.each()) {
        if (!render.visible || !render.sprite) continue;

        renderer->draw(
            pos.value,      // позиция
            render.size,    // размер
            render.sprite,  // спрайт
            render.rotation,// поворот
            render.color    // цвет
        );
    }
}