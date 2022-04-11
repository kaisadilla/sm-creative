#pragma once

#include "root.h"
#include "Mob.h"
#include "Assets.h"

class Player;

class Enemy : public Mob {
protected:
    sf::Sound sound_stomp;
public:
    Enemy(SceneLevel* level, vec2 size, AnimationState& animations);

    virtual void onCollisionWithPlayer(Player& player) = 0;
};