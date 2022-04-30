#pragma once

#include "Tile.h"
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

private:
    bool isHidden;
    ContentType contentType;
    std::unique_ptr<Entity> containedEntity;
    std::unique_ptr<Tile> containedTile;
    i32 maxHitCount;

    State currentState = State::Active;
    i32 currentHits = 0;

public:
    QuestionBlock(const bool isHidden, std::unique_ptr<Entity>& containedEntity, const i32 hitCount);
    QuestionBlock(const bool isHidden, std::unique_ptr<Tile>& containedTile, const i32 hitCount);

    void onCollisionWithPlayer (Collision& collision, Player* player) override {
        if (collision.direction == Direction::UP) {
            currentHits++;
            player->earnCoin();

            if (currentHits >= maxHitCount) {
                currentState = State::Empty;
            }
        }
    };
};