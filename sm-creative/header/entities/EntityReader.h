#pragma once 

#include "root.h"
#include "entities/entities.h"
#include "entities/Entity.h"
#include "libraries/Buffer.hpp"

class EntityReader {
private:
    enum BehaviorIndices {
        ID_VOID = 0,
        ID_SUPER_MUSHROOM = 1,
        ID_GOOMBA = 1'000,
        ID_KOOPA = 1'001,
        ID_VENUS_FIRE_TRAP = 1'002,
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

    static SuperMushroom* getNextSuperMushroom(Buffer& reader);
    static Goomba* getNextGoomba(Buffer& reader);
    static Koopa* getNextKoopa(Buffer& reader);
    static VenusFireTrap* getNextVenusFireTrap(Buffer& reader);
};