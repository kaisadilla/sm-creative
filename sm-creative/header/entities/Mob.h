#pragma once

#include "root.h"
#include "Entity.h"
#include "assets/Assets.h"

class Player;

class Mob : public Entity {
    friend class IAvoidCliffs;

protected:
    sf::Sound sound_kick;
    sf::Sound sound_stomp;

    bool dyingWithStyle = false;

public:
    Mob();

    GameObjectType getType() override { return GameObjectType::Enemy; }

    virtual void onUpdate();

    virtual void onCollisionWithPlayer(Collision& collision, Player* player) override = 0;

    void dieWithStyle(Direction direction);

protected:
    /// <summary>
    /// Returns true if the position of the player relative to this enemy is
    /// considered as stomping this enemy, rather than running into it.
    /// </summary>
    /// <param name="playerCollider"></param>
    virtual bool isBeingTrampledByPlayer(const sf::FloatRect& playerCollider);
};