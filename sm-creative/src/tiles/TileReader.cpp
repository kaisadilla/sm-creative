#include "tiles/TileReader.h"

#include "assets/Assets.h"
#include "tiles/tiles.h"
#include "entities/EntityReader.h"


Tile* TileReader::getNextTile (Buffer& reader, const bool generateCollider) {
    // The position of the cursor before we begin reading this tile.
    const ui32 startOffset = reader.getReadOffset();
    Tile* tile = nullptr;

    const ui32 tileType = reader.readUInt32_LE();

    // position
    const ui16 posX = reader.readUInt16_LE();
    const ui16 posY = reader.readUInt16_LE();
    const ui32 spriteIndex = reader.readUInt32_LE();

    // animations
    const byte animationLength = reader.readUInt8();
    std::vector<SpriteAnimation*> animations(animationLength);

    for (i32 i = 0; i < animationLength; i++) {
        animations[i] = getNextTileAnimation(reader, spriteIndex);
    }

    if (tileType == ID_BLOCK) {
        tile = new Block();
    }
    else if (tileType == ID_BACKGROUND) {
        tile = new BackgroundTile();
    }
    else if (tileType == ID_QUESTION_BLOCK) {
        auto questionBlock = new QuestionBlock();
        questionBlock->isHidden = reader.readUInt8();
        questionBlock->contentType = (QuestionBlock::ContentType)reader.readUInt8();

        if (questionBlock->contentType == (QuestionBlock::ContentType::Entity)) {
            questionBlock->containedEntity = std::unique_ptr<Entity>(EntityReader::getNextEntity(reader, false));
        }
        
        questionBlock->hitMode = (QuestionBlock::HitMode)reader.readUInt8();

        if (questionBlock->hitMode == QuestionBlock::HitMode::N_Times) {
            questionBlock->maxHitCount = reader.readUInt8();
            questionBlock->revertToCoin = reader.readBool();
        }
        else if (questionBlock->hitMode == QuestionBlock::HitMode::N_Seconds) {
            questionBlock->hitTimer = reader.readFloat_LE();
            questionBlock->persistsUntilHit = reader.readBool();
            questionBlock->revertToCoin = reader.readBool();
        }

        questionBlock->initialize();
        tile = questionBlock;
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
        auto pipe = new PipeOrigin();

        pipe->containsEntity = reader.readBool();
        if (pipe->containsEntity) {
            pipe->containedEntity = std::unique_ptr<Entity>(EntityReader::getNextEntity(reader, false));
        }

        pipe->generatesEntity = reader.readBool();
        if (pipe->generatesEntity) {
            pipe->generatedEntity = std::unique_ptr<Entity>(EntityReader::getNextEntity(reader, false));
        }

        pipe->containsWarp = reader.readBool();

        tile = pipe;
    }
    else if (tileType == ID_PIPE_COMPONENT) {

        tile = new PipeComponent();
    }
    else {
        std::cerr << "Invalid tile behavior ID: " << tileType << " (Address: 0x" << std::hex << startOffset << " to " << reader.getReadOffset() << std::dec << ")\n";    }

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

SpriteAnimation* TileReader::getNextTileAnimation(Buffer& reader, const ui32 spriteIndex) {
    const byte animType = reader.readUInt8();

    if (animType == ANIM_TYPE_STATIC) {
        return TileReader::getNextTileStaticAnimation(reader, spriteIndex);
    }
    else if (animType == ANIM_TYPE_DYNAMIC) {
        return TileReader::getNextTileDynamicAnimation(reader, spriteIndex);
    }
    else {
        return nullptr;
    }
}

SpriteAnimation* TileReader::getNextTileStaticAnimation (Buffer& reader, const ui32 spriteIndex) {
    const uvec2 slices(Assets::texturesPerRow, Assets::texturesPerRow);
    const vec2 sliceSize(Assets::tileSize, Assets::tileSize);

    const ui32 sliceCountX = reader.readUInt8();
    const ui32 sliceCountY = reader.readUInt8(); // unused for tiles, always equals 1.
    const ui32 frame = reader.readUInt8();

    const ui32 tileIndex = Assets::tileIndices[spriteIndex][frame];

    return new StaticAnimation(slices, sliceSize, tileIndex);
}

SpriteAnimation* TileReader::getNextTileDynamicAnimation (Buffer& reader, const ui32 spriteIndex) {
    const uvec2 slices(Assets::texturesPerRow, Assets::texturesPerRow);
    const vec2 sliceSize(Assets::tileSize, Assets::tileSize);

    const ui32 sliceCountX = reader.readUInt8();
    const ui32 sliceCountY = reader.readUInt8(); // unused for tiles, always equals 1.

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
