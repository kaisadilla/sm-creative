#pragma once

#include "root.h"
#include "Enemy.h"
#include "JobManager.h"

class Goomba : public Enemy {
private:
    static constexpr f32 SPEED = 32.f;
private:
    /// <summary>
    /// If true, the goomba starts walking to the right instead of to the left.
    /// </summary>
    bool startingDirectionRight;

public:
    Goomba(SceneLevel* level, vec2 size, bool startingDirectionRight);

    GameObjectType getType() override;

    void onStart() override;
    void onUpdate() override;

    void onCollisionWithTile(Collision& collision) override;
    void onCollisionWithPlayer(Player& player) override;

    void die() override;
};

namespace AnimStates::Goomba {
    enum States {
        WALKING = 0,
        DEAD = 1
    };
}