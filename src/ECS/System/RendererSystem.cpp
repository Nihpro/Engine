#include "RendererSystem.h"
#include "../Components/Transform.h"
#include "../Components/Render.h"
#include "../../Renderer/Sprite.h"
#include <algorithm>

void RendererSystem::update(entt::registry& registry) {
    collectRenderCommands(registry, m_commands);
    sortCommands(m_commands);
    executeCommands(m_commands);
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
            render.layer,
            render.currentFrame
            });
    }
}

void RendererSystem::sortCommands(std::vector<RenderCommand>& commands) {
    std::sort(commands.begin(), commands.end(),
        [](const RenderCommand& a, const RenderCommand& b) {
            return a.layer < b.layer;
        });
}

void RendererSystem::executeCommands(const std::vector<RenderCommand>& commands) {
    for (const auto& cmd : commands) {
        cmd.sprite->render(
            cmd.position,
            cmd.size,
            cmd.rotation,
            static_cast<float>(cmd.layer),
            cmd.frameId
        );
    }
}