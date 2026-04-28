#pragma once
#include <memory>
#include "../../Renderer/SpriteAnimator.h"

struct Animation {
    std::shared_ptr<RenderEngine::SpriteAnimator> animator;
    bool playing = true;
};