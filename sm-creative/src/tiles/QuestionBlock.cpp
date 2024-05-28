#include "tiles/QuestionBlock.h"
#include "vfx/EarnedCoinParticle.h"
#include "game/scenes/LevelScene.h"

QuestionBlock::QuestionBlock(const bool isHidden, ContentType contentType, HitMode hitMode) {
    this->isHidden = isHidden;
    this->contentType = contentType;
    this->hitMode = hitMode;
}

void QuestionBlock::initialize () {
    sound_coin.setBuffer(Assets::sound_coin);
    sound_item.setBuffer(Assets::sound_item_spawn);
}

void QuestionBlock::setContainedEntity (std::unique_ptr<Entity>& containedEntity) {
    this->containedEntity = std::move(containedEntity);
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

            //auto& tween = tweeny::uptrFrom(0);
            auto tweeno = tweeny::from(0);
            std::unique_ptr<tweeny::tween<i32>> tween = std::make_unique<tweeny::tween<i32>>(std::move(tweeno));
            tween->to(-10).during(100).via(tweeny::easing::sinusoidalOut).to(0).during(50).via(tweeny::easing::linear);
            animHitByPlayer.setTween(tween);
            animHitByPlayer.start();

            if (contentType == ContentType::Coin) {
                player->earnCoin();
                sound_coin.play();

                std::unique_ptr<Particle> coinParticle = std::make_unique<EarnedCoinParticle>();
                coinParticle->setPosition(position + vec2(0, -16));
                level->instantiateParticle(coinParticle);
            }
            else if (contentType == ContentType::Entity) {
                animHitByPlayer.setEndCallback([this, collision]() {
                    containedEntity->setPosition(position + vec2(0, 0));
                    containedEntity->setStartingDirectionRight(collision.intersection.x > PIXELS_PER_TILE / 2.f);
                    containedEntity->playGetFromBlockAnimation();

                    level->instantiateEntity(containedEntity);
                    sound_item.play();
                });
            }

            if (currentHits >= maxHitCount) {
                currentState = State::Empty;
                animations.setState(AnimState::ANIM_EMPTY);
            }
        }
    }
}