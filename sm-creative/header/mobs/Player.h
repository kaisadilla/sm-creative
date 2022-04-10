#pragma once

#include "root.h"
#include "Mob.h"

class Enemy;

class Player : public Mob {
private:
    static constexpr f32 ACCELERATION_X = 16.f * 16.f;
    static constexpr f32 MAX_SPEED_X = 16.f * 8.f;

private:
    /********
     * JUMP *
     ********/
    f32 jumpStart = 0.f;
    f32 jumpTime = 0.f;
    f32 jumpMinTime = 0.f;
    f32 jumpMaxTime = 0.f;
    bool isJumping = false;

    /**********
     * SOUNDS *
     **********/
    sf::Sound sound_jump;

public:
    Player(SceneLevel* level, vec2 size);

    GameObjectType getType();

    void onStart();
    void onUpdate();
    void onFixedUpdate();

    void checkCollisionWithEnemies(const std::vector<Enemy*>& enemies);

    void killPlayer();

private:
    void onCollisionWithTile(Collision& collision);

    void input();
    void playerJumpStart();
    void playerJump();
    void playerJumpEnd(bool forced);
    void setAnimationState();

    void checkLevelBoundaries();
};

namespace AnimStates::Player {
    enum States {
        STILL_RIGHT   = 0,
        WALKING_RIGHT = 1,
        SKID_RIGHT    = 2,
        JUMPING_RIGHT = 3,
        STILL_LEFT    = 4,
        WALKING_LEFT  = 5,
        SKID_LEFT     = 6,
        JUMPING_LEFT  = 7,
        DEAD          = 8
    };
}