#pragma once
#include <cstdint>
#include <utility>
#include <functional>

const int CHUNK_SIZE = 32;
const float TILE_SIZE = 64.0f;

enum class BlockType : uint8_t {
    Air = 0,
    Dirt = 1,
    Stone = 2,
    Ore = 3
};

struct Chunk
{
    BlockType tiles[CHUNK_SIZE * CHUNK_SIZE];
};

struct ChunkPosHash
{
    std::size_t operator()(const std::pair<int, int>& pos) const {
        return std::hash<int>{}(pos.first) ^ (std::hash<int>{}(pos.second) << 1);
    }
};