#pragma once

#include "root.h"
#include "Enemy.h"

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

    GameObjectType getType();

    void onStart();
    void onUpdate();

    void onCollisionWithTile(Collision& collision);
    void onCollisionWithPlayer(Player& player);
};

namespace AnimStates::Goomba {
    enum States {
        WALKING = 0,
        DEAD = 1
    };
}