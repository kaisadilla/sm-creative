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

public:
    static Entity* getNextEntity(Buffer& reader);
};