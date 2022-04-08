#pragma once

#include "root.h"
#include "Mob.h"

class Player : public Mob {
private:

public:
    Player(SceneLevel* level, vec2 size);

    GameObjectType getType();

    void onStart();
    void onUpdate(const f32 deltaTime);

    void input();
};