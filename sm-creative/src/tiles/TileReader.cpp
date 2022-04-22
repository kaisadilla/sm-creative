#include "tiles/TileReader.h"

#include "assets/Assets.h"
#include "tiles/Block.h"
#include "tiles/BackgroundTile.h"


Tile* TileReader::getNextTile (Buffer& reader) {
    Tile* tile = nullptr;

    const ui32 tileType = reader.readUInt32_LE();

    // position
    const ui16 posX = reader.readUInt16_LE();
    const ui16 posY = reader.readUInt16_LE();

    // sprite
    SpriteAnimation* animation = getNextTileAnimation(reader);

    if (tileType == ID_BLOCK) {
        const bool isHidden = reader.readUInt8();

        tile = new Block(isHidden);
    }
    else if (tileType == ID_BACKGROUND) {
        tile = new BackgroundTile();
    }

    tile->setPosition(ivec2(posX, posY));
    tile->setAnimation(std::unique_ptr<SpriteAnimation>(animation));

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
    const uvec2 slices = uvec2(Assets::texturesPerRow, Assets::texturesPerRow);
    const uvec2 sliceSize = uvec2(Assets::tileSize, Assets::tileSize);

    const ui32 spriteIndex = reader.readUInt32_LE();
    const ui32 tileIndex = Assets::tileIndices[spriteIndex][0];

    return new StaticAnimation(slices, sliceSize, tileIndex);
}

SpriteAnimation* TileReader::getNextTileDynamicAnimation (Buffer& reader) {
    const uvec2 slices = uvec2(Assets::texturesPerRow, Assets::texturesPerRow);
    const uvec2 sliceSize = uvec2(Assets::tileSize, Assets::tileSize);

    const ui32 spriteIndex = reader.readUInt32_LE();
    const ui32 sliceCount = reader.readUInt8();
    // TODO: Remove these from the binary file.
    const ui32 __unused_sizeX = reader.readUInt8();
    const ui32 __unused_sizeY = reader.readUInt8();

    const ui32 framesLength = reader.readUInt8();
    std::vector<ui32> frames(framesLength);
    for (i32 i = 0; i < framesLength; i++) {
        const i32 frame = reader.readUInt8();
        frames[i] = Assets::tileIndices[spriteIndex][frame];
    }

    const ui32 frameTimesLength = reader.readUInt8();

    // frame is a value
    if (frameTimesLength == 0) {
        const ui32 frameTime = reader.readFloat_LE();
        return new DynamicAnimation(frameTime, frames, slices, sliceSize);
    }
    // frame is an array of values.
    else {
        std::vector<f32> frameTimes(frameTimesLength);

        for (i32 i = 0; i < frameTimesLength; i++) {
            frameTimes[i] = reader.readFloat_LE();
        }

        return new DynamicAnimation(frameTimes, frames, slices, sliceSize);
    }
}
