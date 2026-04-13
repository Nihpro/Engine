#pragma once
#include <memory>
#include <vector>

class Sprite;

struct Animation {
    std::vector<std::shared_ptr<Sprite>> frames;
    float currentTime = 0.0f;
    float frameDuration = 0.1f;
    int currentFrame = 0;
    bool loop = true;
    bool playing = true;
};