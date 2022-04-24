#pragma once

#include "root.h"
#include "Mob.h"
#include "JobManager.h"
#include "behavior/IAvoidCliffs.h"

class Koopa : public Mob, public IAvoidCliffs {
private:
    static constexpr f32 WALKING_SPEED = 32.f;
    static constexpr f32 SHELL_SPEED = 32.f * 6.f;

private:
    bool startingDirectionRight;
    bool canRevive;
    bool playerCanGrabShell;

    sf::IntRect shellCollider;

    bool isShell = false;
    bool isReviving = false;
    f32 secondsUntilReviveStart = 6.0f;
    f32 secondsUntilReviveEnd = 1.0f;

public:
    Koopa(bool avoidsCliffs, bool startingDirectionRight, bool canRevive, bool playerCanGrabShell);

    void initialize(const sf::IntRect& shellColliderPosition);
    void initializeAnimations() override;

    void onStart() override;
    void onUpdate() override;
    void onFixedUpdate() override;

    void onCollisionWithTile(Collision& collision, Tile& tile) override;
    void onCollisionWithMob(Collision& collision, Mob* mob) override;
    void onCollisionWithPlayer(Collision& collision, Player& player) override;

    void takeDamage(bool forceDeath, Direction direction = Direction::NONE) override;
    void die() override;

    void turnIntoShell();
    void checkShellRevive();
    void startRevive();
    void revive();
    void pushShell(Direction direction, f32 push);
    void stopShell();

    virtual void drawDebugInfo(sf::RenderWindow& window) override;
};

namespace AnimStates::Koopa {
    enum KoopaState {
        WALKING,
        SHELL,
        SHELL_TRAVELLING,
        SHELL_REANIMATING,
        DEAD
    };
}