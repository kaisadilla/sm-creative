#pragma once

#include "root.h"
#include "animation/StaticAnimation.h"
#include "animation/DynamicAnimation.h"

class Tile {
    friend class TileReader;

protected:
    ivec2 position;
    std::unique_ptr<SpriteAnimation> animation;

public:
    Tile();

protected:
    inline void setPosition (const ivec2& position) {
        this->position = position;
    }

    inline void setAnimation (std::unique_ptr<SpriteAnimation>& animation) {
        this->animation = std::move(animation);
    }
};