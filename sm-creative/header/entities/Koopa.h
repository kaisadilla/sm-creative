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
    sf::IntRect shellCollider;

    bool isShell = false;
    bool isReviving = false;
    f32 secondsUntilReviveStart = 6.0f;
    f32 secondsUntilReviveEnd = 1.0f;

public:
    Koopa(SceneLevel* level, const vec2& size, const sf::IntRect& shellCollider, bool avoidsCliffs, bool startingDirectionRight, bool canRevive);

    void onStart() override;
    void onUpdate() override;
    void onFixedUpdate() override;

    void onCollisionWithTile(Collision& collision) override;
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

    inline SpriteAnimation* getAnimation (KoopaState state) {
        switch (state) {
        case WALKING:
            return new DynamicAnimation(0.2f, { 0, 1 }, uvec2(6, 1), uvec2(18, 27));
        case SHELL:
            return new StaticAnimation(uvec2(6, 1), uvec2(18, 27), 2);
        case SHELL_TRAVELLING:
            return new DynamicAnimation(0.03f, { 2, 3, 4 }, uvec2(6, 1), uvec2(18, 27));
        case SHELL_REANIMATING:
            return new DynamicAnimation(0.1f, { 2, 5 }, uvec2(6, 1), uvec2(18, 27));
        case DEAD:
            return new StaticAnimation(uvec2(6, 1), uvec2(18, 27), 2);
        }
    }
}