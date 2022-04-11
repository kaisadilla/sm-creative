#pragma once

#include "root.h"
#include "Character.h"
#include "Assets.h"

class Player;

class Mob : public Character {
protected:
    sf::Sound sound_stomp;

public:
    Mob(SceneLevel* level, vec2 size, AnimationState& animations);

    virtual void onCollisionWithPlayer(Player& player) = 0;

public:
    inline Collider& getColliderMutable () {
        return collider;
    }
    inline vec2& getVelocityMutable () {
        return velocity;
    }
};