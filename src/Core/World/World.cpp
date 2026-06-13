#include "World.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"


World::World()
{}

void World::update(glm::vec2 playerPos)
{
	int chunkX = static_cast<int>(std::floor(playerPos.x / (CHUNK_SIZE * TILE_SIZE)));
	int chunkY = static_cast<int>(std::floor(playerPos.y / (CHUNK_SIZE * TILE_SIZE)));

	std::vector<std::pair<int, int>> activeChunks;

	for (int x = chunkX - RENDER_DISTANS; x <= chunkX + RENDER_DISTANS; ++x)
	{
		for (int y = chunkY - RENDER_DISTANS; y <= chunkY + RENDER_DISTANS; ++y)
		{
			std::pair<int, int> chunkPos = { x, y };
			activeChunks.push_back(chunkPos);

			if (m_chunks.find(chunkPos) == m_chunks.end()) {
				m_chunks[chunkPos] = m_GenWorld.generateChunk(x, y);
			}
		}
	}

	for (auto it = m_chunks.begin(); it != m_chunks.end();) {
		int cx = it->first.first;
		int cy = it->first.second;

		if (std::abs(cx - chunkX) > RENDER_DISTANS + 1 || std::abs(cy - chunkY) > RENDER_DISTANS + 1) {
			
			//если изменяли чант то сохраняем на диск........


			it = m_chunks.erase(it);//удаляем чанк из памяти
		}
		else {
			++it;//оставляем чанк в памяти
		}
	}
	

}
void World::render(const glm::mat4& viewProjectionMatrix) {
	int count = 0;
    glm::vec2 tileSize(TILE_SIZE, TILE_SIZE);

    // 1. Считаем ОБРАТНУЮ матрицу
    glm::mat4 invVP = glm::inverse(viewProjectionMatrix);

    // 2. Задаем 4 угла экрана в стандартных координатах OpenGL (NDC)
    // W-компонента обязательна должна быть 1.0f для корректного умножения матриц
    glm::vec4 ndcCorners [4] = {
        glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f), // Левый нижний
        glm::vec4(1.0f, -1.0f, 0.0f, 1.0f), // Правый нижний
        glm::vec4(1.0f,  1.0f, 0.0f, 1.0f), // Правый верхний
        glm::vec4(-1.0f,  1.0f, 0.0f, 1.0f)  // Левый верхний
    };

    // Variables для поиска крайних точек видимого мира
    float minX = std::numeric_limits<float>::max();
    float maxX = -std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxY = -std::numeric_limits<float>::max();

    // 3. Переводим углы экрана в мировые пиксели
    for (int i = 0; i < 4; ++i) {
        glm::vec4 worldPos = invVP * ndcCorners[i];

        // Обязательное перспективное деление (на случай, если захочешь сделать 3D перспективу)
        worldPos /= worldPos.w;

        if (worldPos.x < minX) minX = worldPos.x;
        if (worldPos.x > maxX) maxX = worldPos.x;
        if (worldPos.y < minY) minY = worldPos.y;
        if (worldPos.y > maxY) maxY = worldPos.y;
    }

    // 4. Переводим полученные пиксели в индексы тайлов (с запасом в 1 блок)
    

    int startTileX = static_cast<int>(std::floor(minX / TILE_SIZE));
    int endTileX = static_cast<int>(std::floor(maxX / TILE_SIZE));
    int startTileY = static_cast<int>(std::floor(minY / TILE_SIZE));
    int endTileY = static_cast<int>(std::floor(maxY / TILE_SIZE));

    // 5. Твой идеальный "Умный цикл" отрисовки
    for (int worldY = startTileY; worldY <= endTileY; ++worldY) {
        for (int worldX = startTileX; worldX <= endTileX; ++worldX) {

            BlockType type = getBlockAt(worldX, worldY);
            if (type == BlockType::Air) continue;

            // Не забываем прибавлять половину размера, так как твой Sprite рисуется от центра!
            glm::vec2 worldPos(
                (worldX * TILE_SIZE) + (TILE_SIZE / 2.0f),
                (worldY * TILE_SIZE) + (TILE_SIZE / 2.0f)
            );

            std::string spriteName = getSpriteNameForBlock(type);
            auto sprite = ResourceManager::getSprite(spriteName);

            if (sprite) {
                sprite->render(worldPos, tileSize, 0.f, 0.f);
                count++;
            }
        }
    }

	countBlock = count;
}

BlockType World::getBlockAt(int worldX, int worldY)
{
	int chunkX = static_cast<int>(std::floor(static_cast<float>(worldX) / CHUNK_SIZE ));
	int chunkY = static_cast<int>(std::floor(static_cast<float>(worldY) / CHUNK_SIZE ));

	std::pair<int, int> chunkPos = { chunkX, chunkY };

	if (m_chunks.find(chunkPos) == m_chunks.end()) {
		return BlockType::Air;
	}

	int localX = (worldX % CHUNK_SIZE + CHUNK_SIZE) % CHUNK_SIZE;
	int localY = (worldY % CHUNK_SIZE + CHUNK_SIZE) % CHUNK_SIZE;

	int index = localY * CHUNK_SIZE + localX;
	return m_chunks[chunkPos].tiles[index];

}

