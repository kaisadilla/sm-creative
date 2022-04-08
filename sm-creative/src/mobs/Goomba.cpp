#include "mobs/Goomba.h"
#include "game/scenes/SceneLevel.h"

Goomba::Goomba(SceneLevel* level, vec2 size, bool startingDirectionRight) :
    Mob(level, size, Animation(0.2f, {0, 1}, uvec2(48, 16), uvec2(16, 16))),
    startingDirectionRight(startingDirectionRight)
{}

GameObjectType Goomba::getType() {
    return GameObjectType::Enemy;
}

void Goomba::onStart () {
    gravity = 0.f;
    velocity.x = (startingDirectionRight ? 16.f : -16.f) * 2.f;
}

void Goomba::onUpdate (const f32 deltaTime) {
    Mob::onUpdate(deltaTime);
}

void Goomba::onCollision (Collision& collision) {
    if (collision.direction == Direction::LEFT || collision.direction == Direction::RIGHT) {
        velocity.x = -velocity.x;
    }
}
