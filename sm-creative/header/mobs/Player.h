#pragma once

#include "root.h"
#include "Mob.h"

class Player : public Mob {
private:
    vec2 Ovelocity = vec2(0, 0);
    f32 OminVelocity = 1.f;
    f32 OmaxVelocity = 10.f;
    f32 Oacceleration = 1.f;
    f32 Odrag = 0.98f;

    f32 minVelocity = 0.1f;
    f32 maxUp = 9.8f * 16.f;
    f32 maxDown = 9.8f * 16.f;
    f32 maxHoriz = 8.f * 16.f;
    f32 gravityPull = 1.f * 16.f;

public:
    Player(vec2 size);

    GameObjectType getType();

    void onUpdate(const f32 deltaTime);
    void onFixedUpdate(const f32 fixedTime);

    void move2(const vec2& direction);
    void input();

    inline const Collider& getCollider () const {
        return collider;
    }
};