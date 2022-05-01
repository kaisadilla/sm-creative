#pragma once 

#include "root.h"
#include "entities/Entity.h"
#include "libraries/Buffer.hpp"

class EntityReader {
private:
    enum BehaviorIndices {
        ID_VOID = 0,
        ID_SUPER_MUSHROOM,
        ID_GOOMBA = 1'000,
        ID_KOOPA
    };

    enum AnimTypes {
        ANIM_TYPE_STATIC,
        ANIM_TYPE_DYNAMIC
    };

public:
    static Entity* getNextEntity(Buffer& reader);

private:
    static SpriteAnimation* getNextEntityAnimation(Buffer& reader, const vec2& spriteSize);
    static SpriteAnimation* getNextEntityStaticAnimation(Buffer& reader, const vec2& spriteSize);
    static SpriteAnimation* getNextEntityDynamicAnimation(Buffer& reader, const vec2& spriteSize);
};