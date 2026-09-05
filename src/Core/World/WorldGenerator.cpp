#include "WorldGenerator.h"
#include <FastNoiseLite.h>
#include <cstdlib>

Chunk WorldGenerator::generateChunk(int chunkX, int chunkY)
{
    Chunk newChunk;

    //Создание шума
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetSeed(1234);

    //Настраиваем маштаб чем меньше тем крупнее пятна
    noise.SetFrequency(0.05f);


    for (int y = 0; y < CHUNK_SIZE; ++y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {

            int index = y * CHUNK_SIZE + x;

            //вычисление глобальных координат
            float globalX = (chunkX * CHUNK_SIZE) + x;
            float globalY = (chunkY * CHUNK_SIZE) + y;

            //Получаем значения от -1 до 1
            float noiseVal = noise.GetNoise(globalX, globalY);

            //Переводим из диапазона -1, 1 в удобный от 0 до 1
            float normalizedNoise = (noiseVal + 1.f) / 2.f;


            /*if (x == 0 || x == CHUNK_SIZE - 1 || y == 0 || y == CHUNK_SIZE - 1) {
                newChunk.tiles[index] = BlockType::Stone;
            }
            else {*/
                //Если шум больше 0.6 то стаим камень
                if (normalizedNoise > 0.6f) {
                    newChunk.tiles[index] = BlockType::Stone;
                }
                else if (normalizedNoise < 0.2f) {
                    //Руда
                    newChunk.tiles[index] = BlockType::Gold;
                }
                else {
                    //Земля
                    newChunk.tiles[index] = BlockType::Dirt;
                }
               
            //}


        }
    }
    return newChunk;
}
