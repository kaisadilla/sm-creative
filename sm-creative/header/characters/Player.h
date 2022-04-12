#pragma once

#include "root.h"
#include "Entity.h"

class Mob;

class Player : public Entity {
private:
    static constexpr f32 ACCELERATION_X = 16.f * 20.f;
    static constexpr f32 MAX_SPEED_X = 16.f * 5.5f;

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
    sf::Sound sound_death;

public:
    Player(SceneLevel* level, vec2 size);

    GameObjectType getType() override;

    void onStart() override;
    void onUpdate() override;
    void onFixedUpdate() override;

    void checkCollisionWithEnemies(const std::vector<Mob*>& enemies);

    void takeDamage(bool forceDeath) override;
    void die() override;

private:
    void onCollisionWithTile(Collision& collision) override;

    void input();
    void playerJumpStart();
    void playerJump();
    void playerJumpEnd(bool forced);
    void setAnimationState();

    void checkLevelBoundaries();
    void checkLookingLeft() override;
};

namespace AnimStates::Player {
    enum States {
        STILL  ,
        WALKING,
        SKID   ,
        JUMPING,
        DEAD   
    };
}