#pragma once

#include "tile.h"

class PlatformTop : public Tile {

public:
    bool hasMobCollided(const Collision& collision, const vec2& mobVelocity) const override;
};