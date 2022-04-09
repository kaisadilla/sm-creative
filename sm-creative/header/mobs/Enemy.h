#pragma once

#include "root.h"
#include "Mob.h"

class Player;

class Enemy : public Mob {
public:
    Enemy(SceneLevel* level, vec2 size, AnimationState& animations);

    virtual void onCollisionWithPlayer(Player& player) = 0;
};