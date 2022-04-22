#pragma once

#include "tiles/Tile.h"
#include "libraries/Buffer.hpp"

class TileReader {
private:
    enum BehaviorIndices {
        ID_AIR,
        ID_BLOCK,
        ID_BACKGROUND,
        ID_QUESTION_BLOCK,
        ID_DONUT_BLOCK,
        ID_PLATFORM_TOP,
        ID_BREAKABLE_BLOCK,
        ID_PIPE_ORIGIN,
        ID_PIPE_COMPONENT
    };

    enum SpriteTypes {
        SPRITE_TYPE_STATIC,
        SPRITE_TYPE_DYNAMIC
    };

public:
    static Tile* getNextTile(Buffer& reader);

private:
    static SpriteAnimation* getNextTileAnimation(Buffer& reader);
    static SpriteAnimation* getNextTileStaticAnimation(Buffer& reader);
    static SpriteAnimation* getNextTileDynamicAnimation(Buffer& reader);
};