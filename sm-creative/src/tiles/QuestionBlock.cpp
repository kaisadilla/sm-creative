#include "tiles/QuestionBlock.h"

QuestionBlock::QuestionBlock (const bool isHidden, std::unique_ptr<Entity>& containedEntity, const i32 hitCount) {
    this->isHidden = isHidden;
    this->containedEntity = std::move(containedEntity);
    this->hitCount = hitCount;
}

QuestionBlock::QuestionBlock (const bool isHidden, std::unique_ptr<Tile>& containedTile, const i32 hitCount) {
    this->isHidden = isHidden;
    this->containedTile = std::move(containedTile);
    this->hitCount = hitCount;
}
