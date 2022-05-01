#pragma once

#include <tweeny/tweeny.h>

#include "Tile.h"
#include "animation/TweenAnimation.h"
#include "entities/Entity.h"
#include "entities/Player.h"

class QuestionBlock : public Tile {
private:
    enum class ContentType {
        Entity,
        Tile
    };

    enum class State {
        Active,
        Empty
    };

    enum AnimState {
        ANIM_ACTIVE = 0,
        ANIM_EMPTY = 1
    };

private:
    bool isHidden;
    ContentType contentType;
    std::unique_ptr<Entity> containedEntity;
    std::unique_ptr<Tile> containedTile;
    i32 maxHitCount;

    State currentState = State::Active;
    i32 currentHits = 0;

    sf::Sound sound_coin;

    //bool animating = false;
    //tweeny::tween<i32> tween;

    TweenAnimation<i32> animHitByPlayer;

public:
    QuestionBlock(const bool isHidden, std::unique_ptr<Entity>& containedEntity, const i32 hitCount);
    QuestionBlock(const bool isHidden, std::unique_ptr<Tile>& containedTile, const i32 hitCount);

    void initialize();

    void onUpdate() override;

    void onCollisionWithPlayer(Collision& collision, Player* player) override;
};