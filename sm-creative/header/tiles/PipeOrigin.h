#pragma once

#include "Tile.h"
#include "entities/Entity.h"

class PipeOrigin : public Tile {
    friend class TileReader;

private:
    bool containsEntity = false;
    std::unique_ptr<Entity> containedEntity;

    bool generatesEntity = false;
    std::unique_ptr<Entity> generatedEntity;
    i32 maxGenerationCount;

    bool containsWarp = false;

    i32 currentGenerationCount = 0;
};