#pragma once

#include "root.h"
#include "Enemy.h"
#include "JobManager.h"
#include "behavior/IAvoidCliffs.h"

class Goomba : public Enemy, public IAvoidCliffs {
private:
    static constexpr f32 WALKING_SPEED = 32.f;

private:

public:
    Goomba(bool avoidsCliffs);

    void onStart() override;
    void onUpdate() override;
    void onFixedUpdate() override;

    void onCollisionWithTile(Collision& collision, Tile& tile) override;
    void onCollisionWithEnemy(Collision& collision, Enemy* enemy) override;
    void onCollisionWithPlayer(Collision& collision, Player* player) override;

    void takeDamage(bool forceDeath, Direction direction = Direction::NONE) override;
    void die() override;

    virtual void drawDebugInfo(sf::RenderWindow& window) override;
};

namespace AnimStates::Goomba {
    enum States {
        WALKING = 0,
        STOMPED = 1
    };
}