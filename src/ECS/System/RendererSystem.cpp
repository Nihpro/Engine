#include "RendererSystem.h"
#include "../Components/Transform.h"
#include "../Components/Render.h"
#include "../../Renderer/Renderer.h"
#include "../../Renderer/Sprite.h"
#include <algorithm>  // для std::sort

void RendererSystem::update(entt::registry& registry, Renderer* renderer) {
    if (!renderer) return;

    // 1. Собираем все команды рендеринга
    collectRenderCommands(registry, m_commands);

    // 2. Сортируем по zOrder (от меньшего к большему)
    sortCommands(m_commands);

    // 3. Выполняем команды
    executeCommands(m_commands, renderer);

    // 4. Очищаем для следующего кадра
    m_commands.clear();
}

void RendererSystem::collectRenderCommands(entt::registry& registry, std::vector<RenderCommand>& commands) {
    auto view = registry.view<Position, Renderable>();

    for (auto [entity, pos, render] : view.each()) {
        if (!render.visible || !render.sprite) continue;

        commands.push_back({
            entity,
            pos.value,
            render.size,
            render.sprite,
            render.rotation,
            render.color,
            render.layer
            });
    }
}

void RendererSystem::sortCommands(std::vector<RenderCommand>& commands) {
    // Сортируем по zOrder (по возрастанию)
    std::sort(commands.begin(), commands.end(),
        [](const RenderCommand& a, const RenderCommand& b) {
            return a.zOrder < b.zOrder;
        });
}

void RendererSystem::executeCommands(const std::vector<RenderCommand>& commands, Renderer* renderer) {
    for (const auto& cmd : commands) {
        renderer->draw(
            cmd.position,
            cmd.size,
            cmd.sprite,
            cmd.rotation,
            cmd.color
        );
    }
}