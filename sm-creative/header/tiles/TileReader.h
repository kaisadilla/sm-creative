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

    enum AnimTypes {
        ANIM_TYPE_STATIC,
        ANIM_TYPE_DYNAMIC
    };

    enum ContentType {
        CONTENT_TYPE_ENTITY,
        CONTENT_TYPE_TILE
    };

public:
    static Tile* getNextTile(Buffer& reader, const bool generateCollider);

private:
    static SpriteAnimation* getNextTileAnimation(Buffer& reader, const ui32 spriteIndex);
    static SpriteAnimation* getNextTileStaticAnimation(Buffer& reader, const ui32 spriteIndex);
    static SpriteAnimation* getNextTileDynamicAnimation(Buffer& reader, const ui32 spriteIndex);
};