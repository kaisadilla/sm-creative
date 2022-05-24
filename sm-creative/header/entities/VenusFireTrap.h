#pragma once

#include "root.h"
#include "Enemy.h"

class VenusFireTrap : public Enemy {
    friend class EntityReader;

private:
    i32 projectileCount = 1;
    bool canBeStomped = false;

public:
    void onCollisionWithPlayer(Collision& collision, Player* player) override;

    void takeDamage(bool forceDeath, Direction direction = Direction::NONE) override;
};