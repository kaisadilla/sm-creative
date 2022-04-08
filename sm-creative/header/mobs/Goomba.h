#pragma once

#include "root.h"
#include "Mob.h"

class Goomba : public Mob {
private:
    /// <summary>
    /// If true, the goomba starts walking to the right instead of to the left.
    /// </summary>
    bool startingDirectionRight;

public:
    Goomba(SceneLevel* level, vec2 size, bool startingDirectionRight);

    GameObjectType getType();

    void onStart();
    void onUpdate(const f32 deltaTime);

    void onCollision(Collision& collision);
};