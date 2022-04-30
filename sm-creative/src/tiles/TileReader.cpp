#include "tiles/TileReader.h"

#include "assets/Assets.h"
#include "tiles/tiles.h"


Tile* TileReader::getNextTile (Buffer& reader, const bool generateCollider) {
    // The position of the cursor before we begin reading this tile.
    const ui32 startOffset = reader.getReadOffset();
    Tile* tile = nullptr;

    const ui32 tileType = reader.readUInt32_LE();

    // position
    const ui16 posX = reader.readUInt16_LE();
    const ui16 posY = reader.readUInt16_LE();

    // animations
    const byte animationLength = reader.readUInt8();
    std::vector<SpriteAnimation*> animations(animationLength);

    for (i32 i = 0; i < animationLength; i++) {
        animations[i] = getNextTileAnimation(reader);
    }

    if (tileType == ID_BLOCK) {
        const bool isHidden = reader.readUInt8();

        tile = new Block(isHidden);
    }
    else if (tileType == ID_BACKGROUND) {
        tile = new BackgroundTile();
    }
    else if (tileType == ID_QUESTION_BLOCK) {
        const bool isHidden = reader.readUInt8();
        const byte contentType = reader.readUInt8();
        const byte hitCount = reader.readUInt8();

        tile = new QuestionBlock(isHidden, std::unique_ptr<Entity>(), hitCount);
        ((QuestionBlock*)tile)->initialize();
    }
    else if (tileType == ID_DONUT_BLOCK) {
        tile = new DonutBlock();
    }
    else if (tileType == ID_PLATFORM_TOP) {
        tile = new PlatformTop();
    }
    else if (tileType == ID_BREAKABLE_BLOCK) {
        tile = new BreakableBlock();
    }
    else if (tileType == ID_PIPE_ORIGIN) {
        const bool containsWarp = reader.readUInt8();
        const bool containsEntity = reader.readUInt8();
        tile = new PipeOrigin();
    }
    else if (tileType == ID_PIPE_COMPONENT) {
        tile = new PipeComponent();
    }
    else {
        std::cerr << "Invalid tile behavior ID: " << tileType << " (Address: 0x" << std::hex << startOffset << "|" << reader.getReadOffset() << std::dec << ")\n";
    }

    if (tile != nullptr) {
        tile->setGridPosition(ivec2(posX, posY));

        for (auto& anim : animations) {
            tile->animations.addAnimation(std::unique_ptr<SpriteAnimation>(anim));
        }

        if (generateCollider) {
            const vec2 colliderPosition = vec2(posX * PIXELS_PER_TILE, posY * PIXELS_PER_TILE);
            const vec2 colliderCenter = vec2(PIXELS_PER_TILE / 2.f, PIXELS_PER_TILE / 2.f);
            const vec2 colliderDistanceToEdge = vec2(PIXELS_PER_TILE / 2.f, PIXELS_PER_TILE / 2.f);

            tile->collider = Collider(tile, colliderPosition, colliderCenter, colliderDistanceToEdge);
        }
    }

    return tile;
}

SpriteAnimation* TileReader::getNextTileAnimation(Buffer& reader) {
    const byte spriteType = reader.readUInt8();

    if (spriteType == SPRITE_TYPE_STATIC) {
        return TileReader::getNextTileStaticAnimation(reader);
    }
    else if (spriteType == SPRITE_TYPE_DYNAMIC) {
        return TileReader::getNextTileDynamicAnimation(reader);
    }
    else {
        return nullptr;
    }
}

SpriteAnimation* TileReader::getNextTileStaticAnimation (Buffer& reader) {
    const uvec2 slices(Assets::texturesPerRow, Assets::texturesPerRow);
    const vec2 sliceSize(Assets::tileSize, Assets::tileSize);

    const ui32 spriteIndex = reader.readUInt32_LE();
    const ui32 sliceCount = reader.readUInt8();
    const ui32 frame = reader.readUInt8();

    const ui32 tileIndex = Assets::tileIndices[spriteIndex][frame];

    return new StaticAnimation(slices, sliceSize, tileIndex);
}

SpriteAnimation* TileReader::getNextTileDynamicAnimation (Buffer& reader) {
    const uvec2 slices(Assets::texturesPerRow, Assets::texturesPerRow);
    const vec2 sliceSize(Assets::tileSize, Assets::tileSize);

    const ui32 spriteIndex = reader.readUInt32_LE();
    const ui32 sliceCount = reader.readUInt8();

    const ui32 framesLength = reader.readUInt8();
    std::vector<ui32> frames(framesLength);
    for (i32 i = 0; i < framesLength; i++) {
        const i32 frame = reader.readUInt8();
        frames[i] = Assets::tileIndices[spriteIndex][frame];
    }

    const ui32 frameTimesLength = reader.readUInt8();

    // frame is a value
    if (frameTimesLength == 0) {
        f32 frameTime = reader.readFloat_LE();
        return new DynamicAnimation(slices, sliceSize, frameTime, frames);
    }
    // frame is an array of values.
    else {
        std::vector<f32> frameTimes(frameTimesLength);

        for (i32 i = 0; i < frameTimesLength; i++) {
            frameTimes[i] = reader.readFloat_LE();
        }

        return new DynamicAnimation(slices, sliceSize, frameTimes, frames);
    }
}
