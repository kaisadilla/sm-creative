#pragma once

#include "root.h"
#include "Entity.h"
#include "Assets.h"

class Player;

class Mob : public Entity {
    friend class IAvoidCliffs;

protected:
    sf::Sound sound_stomp;

    f32 despawnTimer;

public:
    Mob(SceneLevel* level, const vec2& size, AnimationState& animations);

    void checkCollisionWithEnemies(const std::vector<Mob*>& enemies, int start);

    virtual void onUpdate();

    virtual void onCollisionWithMob(Collision& collision, Mob* mob) {};
    virtual void onCollisionWithPlayer(Collision& collision, Player& player) = 0;

    void dieWithStyle();
};