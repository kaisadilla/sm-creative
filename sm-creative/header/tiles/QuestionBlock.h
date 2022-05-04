#pragma once

#include <tweeny/tweeny.h>

#include "Tile.h"
#include "animation/TweenAnimation.h"
#include "entities/Entity.h"
#include "entities/Player.h"

class QuestionBlock : public Tile {
public:
    enum class ContentType : byte {
        Coin,
        Entity,
        Tile
    };

    enum class HitMode : byte {
        Once,
        N_Times,
        N_Seconds
    };

    enum class State {
        Active,
        Empty
    };

private:

    enum AnimState {
        ANIM_ACTIVE = 0,
        ANIM_EMPTY = 1
    };

private:
    bool isHidden;
    ContentType contentType;
    HitMode hitMode;

    std::unique_ptr<Entity> containedEntity;
    std::unique_ptr<Tile> containedTile;
    i32 maxHitCount = 1;

    State currentState = State::Active;
    i32 currentHits = 0;

    sf::Sound sound_coin;
    sf::Sound sound_item;

    //bool animating = false;
    //tweeny::tween<i32> tween;

    TweenAnimation<i32> animHitByPlayer;

public:
    QuestionBlock(const bool isHidden, ContentType contentType, HitMode hitMode);

    void initialize();
    void setContainedEntity(std::unique_ptr<Entity>& containedEntity);

    void onUpdate() override;

    void onCollisionWithPlayer(Collision& collision, Player* player) override;
};