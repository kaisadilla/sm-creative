#include "entities/EntityReader.h"
#include "entities/entities.h"

Entity* EntityReader::getNextEntity (Buffer& reader, bool hasLevelSettings) {
    Entity* entity = nullptr;

    const ui32 entityType = reader.readUInt32_LE();

    // sprite
    const byte entitySizeX = reader.readUInt8();
    const byte entitySizeY = reader.readUInt8();
    const byte spriteSizeX = reader.readUInt8();
    const byte spriteSizeY = reader.readUInt8();
    const byte colliderTop = reader.readUInt8();
    const byte colliderLeft = reader.readUInt8();
    const byte colliderWidth = reader.readUInt8();
    const byte colliderHeight = reader.readUInt8();

    const vec2 entitySize(entitySizeX, entitySizeY);
    const vec2 spriteSize(spriteSizeX, spriteSizeY);
    const sf::IntRect collider(colliderTop, colliderLeft, colliderWidth, colliderHeight);

    const ui32 spriteIndex = reader.readUInt32_LE();
    // animations
    const byte animationLength = reader.readUInt8();
    std::vector<SpriteAnimation*> animations(animationLength);

    for (i32 i = 0; i < animationLength; i++) {
        animations[i] = getNextEntityAnimation(reader, spriteSize);
    }
    
    if (entityType == ID_SUPER_MUSHROOM) {
        const byte effectOnPlayer = reader.readUInt8(); // discarded for now

        entity = new SuperMushroom();

    }
    else if (entityType == ID_GOOMBA) {
        const bool avoidsCliffs = reader.readUInt8();

        entity = new Goomba(avoidsCliffs);
    }
    else if (entityType == ID_KOOPA) {
        const byte shellColliderTop = reader.readUInt8();
        const byte shellColliderLeft = reader.readUInt8();
        const byte shellColliderWidth = reader.readUInt8();
        const byte shellColliderHeight = reader.readUInt8();

        const bool avoidsCliffs = reader.readUInt8();
        const bool canRevive = reader.readUInt8();
        const bool playerCanGrabShell = reader.readUInt8();

        entity = new Koopa(avoidsCliffs, canRevive, playerCanGrabShell);
        ((Koopa*)entity)->initialize(sf::IntRect(shellColliderTop, shellColliderLeft, shellColliderWidth, shellColliderHeight));
    }
    else {
        std::cerr << "Invalid entity behavior ID: " << entityType << "\n";
    }

    if (entity != nullptr) {
        entity->setDefaultSizes(entitySize, spriteSize, collider);
        entity->setSprite(spriteIndex);

        for (auto& anim : animations) {
            entity->animations.addAnimation(std::unique_ptr<SpriteAnimation>(anim));
        }

        if (hasLevelSettings) {
            // position
            const ui16 posX = reader.readUInt16_LE();
            const ui16 posY = reader.readUInt16_LE();

            const bool startingDirectionRight = reader.readUInt8();

            entity->setGridPosition(ivec2(posX, posY));
            entity->setStartingDirectionRight(startingDirectionRight);
        }
    }

    return entity;
}

SpriteAnimation* EntityReader::getNextEntityAnimation (Buffer& reader, const vec2& spriteSize) {
    const byte spriteType = reader.readUInt8();

    if (spriteType == ANIM_TYPE_STATIC) {
        return EntityReader::getNextEntityStaticAnimation(reader, spriteSize);
    }
    else if (spriteType == ANIM_TYPE_DYNAMIC) {
        return EntityReader::getNextEntityDynamicAnimation(reader, spriteSize);
    }
    else {
        return nullptr;
    }
}

SpriteAnimation* EntityReader::getNextEntityStaticAnimation (Buffer& reader, const vec2& spriteSize) {
    const ui32 slicesX = reader.readUInt8();
    const ui32 slicesY = reader.readUInt8();
    const ui32 frame = reader.readUInt8();

    return new StaticAnimation(uvec2(slicesX, slicesY), spriteSize, frame);
}

SpriteAnimation* EntityReader::getNextEntityDynamicAnimation (Buffer& reader, const vec2& spriteSize) {
    const ui32 slicesX = reader.readUInt8();
    const ui32 slicesY = reader.readUInt8();

    const ui32 framesLength = reader.readUInt8();
    std::vector<ui32> frames(framesLength);
    for (i32 i = 0; i < framesLength; i++) {
        frames[i] = reader.readUInt8();
    }

    const ui32 frameTimesLength = reader.readUInt8();

    // frame is a value
    if (frameTimesLength == 0) {
        f32 frameTime = reader.readFloat_LE();
        return new DynamicAnimation(uvec2(slicesX, slicesY), spriteSize, frameTime, frames);
    }
    // frame is an array of values.
    else {
        std::vector<f32> frameTimes(frameTimesLength);

        for (i32 i = 0; i < frameTimesLength; i++) {
            frameTimes[i] = reader.readFloat_LE();
        }

        return new DynamicAnimation(uvec2(slicesX, slicesY), spriteSize, frameTimes, frames);
    }
}
