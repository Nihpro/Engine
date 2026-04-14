#pragma once
#include <entt.hpp>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class Renderer;
class Sprite;

struct RenderCommand {
    entt::entity entity;
    glm::vec2 position;
    glm::vec2 size;
    std::shared_ptr<Sprite> sprite;
    float rotation;
    glm::vec3 color;
    int zOrder;
};

class RendererSystem {
public:
    void update(entt::registry& registry, Renderer* renderer);

private:
    void collectRenderCommands(entt::registry& registry, std::vector<RenderCommand>& commands);
    void sortCommands(std::vector<RenderCommand>& commands);
    void executeCommands(const std::vector<RenderCommand>& commands, Renderer* renderer);

    std::vector<RenderCommand> m_commands;  // переиспользуем для производительности
};