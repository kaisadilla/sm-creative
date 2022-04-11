#pragma once

#include "root.h"
#include "Mob.h"
#include "JobManager.h"

class Goomba : public Mob {
private:
    static constexpr f32 SPEED = 32.f;

    enum AnimStates {
        WALKING = 0,
        DEAD = 1
    };

private:
    bool avoidsCliffs;
    /// <summary>
    /// If true, the goomba starts walking to the right instead of to the left.
    /// </summary>
    bool startingDirectionRight;

    ivec2 checkedCliffTile;

    /*********
     * DEBUG *
     *********/
    sf::RectangleShape debug_checkedCliffTile;

public:
    Goomba(SceneLevel* level, const vec2& size, bool avoidsCliffs, bool startingDirectionRight);

    GameObjectType getType() override;

    void onStart() override;
    void onUpdate() override;

    void onCollisionWithTile(Collision& collision) override;
    void onCollisionWithPlayer(Player& player) override;

    void die() override;

    virtual void drawDebugInfo(sf::RenderWindow& window) override;

public:
    void checkCliffs();
};

//namespace AnimStates::Goomba {
//    enum States {
//        WALKING = 0,
//        DEAD = 1
//    };
//}