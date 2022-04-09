#pragma once

#include "root.h"
#include "Mob.h"

class Enemy;

class Player : public Mob {
private:
    static constexpr f32 ACCELERATION_X = 16.f * 16.f;
    static constexpr f32 MAX_SPEED_X = 16.f * 8.f;

public:
    Player(SceneLevel* level, vec2 size);

    GameObjectType getType();

    void onStart();
    void onUpdate(const f32 deltaTime);
    void onFixedUpdate(const f32 fixedTime);

    void checkCollisionWithEnemies(const std::vector<Enemy*>& enemies);

    void killPlayer();

private:
    void input(const f32 deltaTime);
    void setAnimationState();

    void checkLevelBoundaries();
};

namespace AnimStates::Player {
    enum States {
        STILL = 0,
        WALKING = 1,
        DEAD = 2
    };
}