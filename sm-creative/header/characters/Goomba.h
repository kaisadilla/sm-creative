#pragma once

#include "root.h"
#include "Mob.h"
#include "JobManager.h"
#include "behavior/IAvoidCliffs.h"

class Goomba : public Mob, public IAvoidCliffs {
private:
    static constexpr f32 WALKING_SPEED = 32.f;

private:
    /// <summary>
    /// If true, the goomba starts walking to the right instead of to the left.
    /// </summary>
    bool startingDirectionRight;

public:
    Goomba(SceneLevel* level, const vec2& size, bool avoidsCliffs, bool startingDirectionRight);

    GameObjectType getType() override { return GameObjectType::Enemy; }

    void onStart() override;
    void onUpdate() override;
    void onFixedUpdate() override;

    void onCollisionWithTile(Collision& collision) override;
    void onCollisionWithMob(Collision& collision, Mob* mob) override;
    void onCollisionWithPlayer(Collision& collision, Player& player) override;

    void takeDamage(bool forceDeath) override;
    void die() override;

    virtual void drawDebugInfo(sf::RenderWindow& window) override;
};

namespace AnimStates::Goomba {
    enum States {
        WALKING = 0,
        STOMPED = 1
    };
}