#pragma once
#include <entt.hpp>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace RenderEngine {
    class Sprite;
}

struct RenderCommand {
    entt::entity entity;
    glm::vec2 position;
    glm::vec2 size;
    std::shared_ptr<RenderEngine::Sprite> sprite;
    float rotation;
    glm::vec3 color;
    int layer;
    size_t frameId;
};

class RendererSystem {
public:
    void update(entt::registry& registry);

private:
    void collectRenderCommands(entt::registry& registry, std::vector<RenderCommand>& commands);
    void sortCommands(std::vector<RenderCommand>& commands);
    void executeCommands(const std::vector<RenderCommand>& commands);

    std::vector<RenderCommand> m_commands;
};