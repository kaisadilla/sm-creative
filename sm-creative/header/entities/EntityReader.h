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
    /// <summary>
    /// Reads an entity from the current position in the buffer given.
    /// </summary>
    /// <param name="reader">A buffer containing the binary, with the cursor in which to read the entity.</param>
    /// <param name="hasLevelSettings">If true, the encoded entity contains level settings information (such as its position)</param>
    /// <returns></returns>
    static Entity* getNextEntity(Buffer& reader, bool hasLevelSettings);

private:
    static SpriteAnimation* getNextEntityAnimation(Buffer& reader, const vec2& spriteSize);
    static SpriteAnimation* getNextEntityStaticAnimation(Buffer& reader, const vec2& spriteSize);
    static SpriteAnimation* getNextEntityDynamicAnimation(Buffer& reader, const vec2& spriteSize);
};