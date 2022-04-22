#pragma once

#include "Tile.h"
#include "entities/Entity.h"

class QuestionBlock : public Tile {
private:
    enum class ContentType {
        Entity,
        Tile
    };

private:
    bool isHidden;
    ContentType contentType;
    std::unique_ptr<Entity> containedEntity;
    std::unique_ptr<Tile> containedTile;
    i32 hitCount;

public:
    QuestionBlock(const bool isHidden, std::unique_ptr<Entity>& containedEntity, const i32 hitCount);
    QuestionBlock(const bool isHidden, std::unique_ptr<Tile>& containedTile, const i32 hitCount);
};