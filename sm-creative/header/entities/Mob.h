#pragma once

#include "root.h"
#include "Entity.h"
#include "assets/Assets.h"

class Player;

class Mob : public Entity {
    friend class IAvoidCliffs;

protected:
    sf::Sound sound_stomp;

    bool dyingWithStyle = false;

    sf::Sound sound_kick;

public:
    Mob(SceneLevel* level, const vec2& size, AnimationState& animations);

    GameObjectType getType() override { return GameObjectType::Enemy; }

    void checkCollisionWithEnemies(const std::vector<Mob*>& enemies, int start);

    virtual void onUpdate();

    virtual void onCollisionWithMob(Collision& collision, Mob* mob) {};
    virtual void onCollisionWithPlayer(Collision& collision, Player& player) override = 0;

    void dieWithStyle(Direction direction);

protected:
    /// <summary>
    /// Returns true if the player is in a position where it should be
    /// considered they are stepping on the mob, rather than running into it.
    /// </summary>
    /// <param name="playerCollider"></param>
    virtual bool isBeingTrampledByPlayer(const sf::FloatRect& playerCollider);
};