#pragma once
#include "WorldDefines.h"
#include "WorldGenerator.h"
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

class World
{
public:
	World();
	void update(glm::vec2 playerPos);
	void render(const glm::mat4& viewProjectionMatrix);
	BlockType getBlockAt(int worldX, int worldY);

	int GetCountRenderBlock() { return countBlock; }
	

private:
	std::unordered_map<std::pair<int, int>, Chunk, ChunkPosHash> m_chunks;
	WorldGenerator m_GenWorld;

	const int RENDER_DISTANS = 2;
	int countBlock;

	std::string getSpriteNameForBlock(BlockType type) {
		
		switch (type) {
		case BlockType::Dirt:  return "Dirt"; 
		case BlockType::Stone: return "Stone";
		case BlockType::Gold:   return "Gold";
		default:               return "Box";         // Фолбэк (если текстура не найдена)
		}
	}
};