#pragma once

#include "root.h"
#include "Entity.h"

class Mob;
class Item;

class Player : public Entity {
private:
    static constexpr f32 ACCELERATION_X = 16.f * 20.f;
    static constexpr f32 MAX_SPEED_X = 16.f * 5.5f;

public:
    enum class MarioMode {
        SMALL = 0,
        BIG = 1,
        FIRE = 2,
        RACCOON = 3,
        FROG = 4,
        TANOOKI = 5,
        HAMMER = 6
    };
    enum AnimState {
        ANIM_SMALL_STILL,
        ANIM_SMALL_WALKING,
        ANIM_SMALL_SKID,
        ANIM_SMALL_JUMPING,
        ANIM_DEAD,
        ANIM_BIG_STILL,
        ANIM_BIG_WALKING,
        ANIM_BIG_SKID,
        ANIM_BIG_JUMPING,
        ANIM_BIG_CROUCHING,
        ANIM_TRANSFORM_SMALL_TO_BIG
    };

private:
    MarioMode currentMode = MarioMode::SMALL;

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
    Player();

    GameObjectType getType() override;
    void initializeAnimations() override;

    void onStart() override;
    void onUpdate() override;
    void onFixedUpdate() override;

    void checkCollisionWithEnemies(const std::vector<Mob*>& enemies);
    void checkCollisionWithItems(const std::vector<std::unique_ptr<Item>>& items);

    void setMode(MarioMode mode);
    void takeDamage(bool forceDeath, Direction direction = Direction::NONE) override;
    void die() override;

private:
    void onCollisionWithTile(Collision& collision) override;

    void input();
    void playerJumpStart();
    void playerJump();
    void playerJumpEnd(bool forced);

    void checkLevelBoundaries();
    void checkLookingLeft() override;

    void setAnimationState();
    void updateColliderDimensions();

private:
    inline AnimState getCurrentAnimState_still () {
        switch (currentMode) {
        case MarioMode::SMALL:
            return AnimState::ANIM_SMALL_STILL;
        case MarioMode::BIG:
            return AnimState::ANIM_BIG_STILL;
        default:
            return AnimState::ANIM_SMALL_STILL;
        }
    }

    inline AnimState getCurrentAnimState_walking () {
        switch (currentMode) {
        case MarioMode::SMALL:
            return AnimState::ANIM_SMALL_WALKING;
        case MarioMode::BIG:
            return AnimState::ANIM_BIG_WALKING;
        default:
            return AnimState::ANIM_SMALL_WALKING;
        }
    }

    inline AnimState getCurrentAnimState_skid () {
        switch (currentMode) {
        case MarioMode::SMALL:
            return AnimState::ANIM_SMALL_SKID;
        case MarioMode::BIG:
            return AnimState::ANIM_BIG_SKID;
        default:
            return AnimState::ANIM_SMALL_SKID;
        }
    }

    inline AnimState getCurrentAnimState_jumping () {
        switch (currentMode) {
        case MarioMode::SMALL:
            return AnimState::ANIM_SMALL_JUMPING;
        case MarioMode::BIG:
            return AnimState::ANIM_BIG_JUMPING;
        default:
            return AnimState::ANIM_SMALL_JUMPING;
        }
    }

    inline const AnimState& getCurrentAnimState_crouching () {
        switch (currentMode) {
        case MarioMode::SMALL:
            return AnimState::ANIM_SMALL_STILL;
        case MarioMode::BIG:
            return AnimState::ANIM_BIG_CROUCHING;
        default:
            return AnimState::ANIM_SMALL_STILL;
        }
    }
};