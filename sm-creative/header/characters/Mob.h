#pragma once

#include "root.h"
#include "Character.h"
#include "Assets.h"

class Player;

class Mob : public Character {
protected:
    sf::Sound sound_stomp;

public:
    Mob(SceneLevel* level, const vec2& size, AnimationState& animations);

    virtual void onCollisionWithPlayer(Player& player) = 0;
};