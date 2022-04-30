#include "tiles/QuestionBlock.h"

QuestionBlock::QuestionBlock (const bool isHidden, std::unique_ptr<Entity>& containedEntity, const i32 hitCount) {
    this->isHidden = isHidden;
    this->containedEntity = std::move(containedEntity);
    this->maxHitCount = hitCount;
}

QuestionBlock::QuestionBlock (const bool isHidden, std::unique_ptr<Tile>& containedTile, const i32 hitCount) {
    this->isHidden = isHidden;
    this->containedTile = std::move(containedTile);
    this->maxHitCount = hitCount;
}

void QuestionBlock::initialize () {
    sound_coin.setBuffer(Assets::sound_coin);
}

void QuestionBlock::onCollisionWithPlayer (Collision& collision, Player* player) {
    if (collision.direction == Direction::UP) {
        if (currentState == State::Active) {
            currentHits++;
            player->earnCoin();
            sound_coin.play();

            if (currentHits >= maxHitCount) {
                currentState = State::Empty;
                animations.setState(AnimState::ANIM_EMPTY);
            }
        }
    }
}