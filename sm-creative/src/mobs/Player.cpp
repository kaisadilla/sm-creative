#include "mobs/Player.h"

Player::Player (vec2 size) : Mob(size) {}

GameObjectType Player::getType () {
    return GameObjectType::Tile;
}

void Player::onUpdate (const f32 deltaTime) {
    input();
}

void Player::onFixedUpdate (const f32 fixedTime) {
    updatePhysics(fixedTime);
}

void Player::move2 (const vec2& direction) {
    // Accelerate
    //velocity.x += direction.x * acceleration;
    //velocity.y += direction.y * acceleration;

    Ovelocity += direction * Oacceleration;

    // Limit velocity
    Ovelocity.x = std::clamp(Ovelocity.x, -OmaxVelocity, OmaxVelocity);
    Ovelocity.y = std::clamp(Ovelocity.y, -OmaxVelocity, OmaxVelocity);
}

void Player::input () {
    f32 horizontalSpeed = 16.f * 8.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        horizontalSpeed *= 2.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocity.x = -horizontalSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocity.x = horizontalSpeed;
    }
    else {
        velocity.x = 0;
    }

    if (isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        velocity.y = -40.f * 16.f;
    }
}