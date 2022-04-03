#include "mobs/Player.h"

Player::Player (vec2 size) : Mob(size), collider(position + size / 2.f, vec2((size.x / 2.f) - 1, size.y / 2.f)) {}

void Player::onUpdate (const f32 deltaTime, const std::vector<Collider>& __testc) {
    updatePhysics(deltaTime);
    collider.setCenter(position + size / 2.f);

    bool collided = false;
    for (const Collider& otherCollider : __testc) {
        bool colision = collider.checkColision(otherCollider);
        if (colision) {
            collided = true;
        }
    }

    sprite.setFillColor(collided ? sf::Color::Red : sf::Color::White);
}

void Player::move2 (const vec2& direction) {
    // Accelerate
    //velocity.x += direction.x * acceleration;
    //velocity.y += direction.y * acceleration;

    velocity += direction * acceleration;

    // Limit velocity
    velocity.x = std::clamp(velocity.x, -maxVelocity, maxVelocity);
    velocity.y = std::clamp(velocity.y, -maxVelocity, maxVelocity);
}

void Player::updatePhysics (const f32 deltaTime) {
    velocity.x *= drag;

    if (std::abs(velocity.x) < minVelocity) {
        velocity.x = 0.f;
    }
    if (std::abs(velocity.y) < minVelocity) {
        velocity.y = 0.f;
    }
}
