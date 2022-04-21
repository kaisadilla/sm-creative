#pragma once

#include "root.h"
#include "Item.h"

class SuperMushroom : public Item {
private:
    static constexpr f32 SPEED_X = 16.f * 5.f;
    static constexpr f32 SPEED_Y = 16.f * 10.f;

private:
    bool startingDirectionRight;

public:
    SuperMushroom(SceneLevel* level, const vec2& size, bool startingDirectionRight);

    void onStart() override;
    void onUpdate() override;

    void onCollisionWithTile(Collision& collision) override;
    void onCollisionWithPlayer(Collision& collision, Player& player) override;

    void updatePhysics() override;

private:
};