#pragma once

#include "root.h"
#include "entities/Entity.h"

class Item : public Entity {
public:
    Item() {};

    GameObjectType getType() override { return GameObjectType::Item; }

    virtual void onCollisionWithPlayer(Collision& collision, Player* player) override = 0;

    virtual void takeDamage(bool forceDeath, Direction direction = Direction::NONE);
};