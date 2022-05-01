#include "tiles/QuestionBlock.h"
#include "vfx/EarnedCoinParticle.h"
#include "game/scenes/LevelScene.h"

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

void QuestionBlock::onUpdate () {
    Tile::onUpdate();

    animHitByPlayer.onUpdate([this](i32 yOffset) {
        setDrawPosition(position + vec2(0, yOffset));
    });
}

void QuestionBlock::onCollisionWithPlayer (Collision& collision, Player* player) {
    if (collision.direction == Direction::UP) {
        if (currentState == State::Active) {
            currentHits++;
            player->earnCoin();
            sound_coin.play();

            auto& tween = tweeny::uptrFrom(0);
            tween->to(-10).during(100).via(tweeny::easing::sinusoidalOut).to(0).during(50).via(tweeny::easing::linear);
            animHitByPlayer.setTween(tween);
            animHitByPlayer.start();

            std::unique_ptr<Particle> coinParticle = std::make_unique<EarnedCoinParticle>();
            coinParticle->setPosition(position + vec2(0, -16));
            level->instantiateParticle(coinParticle);

            if (currentHits >= maxHitCount) {
                currentState = State::Empty;
                animations.setState(AnimState::ANIM_EMPTY);
            }
        }
    }
}