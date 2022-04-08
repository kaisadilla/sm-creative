#include "mobs/Player.h"
#include "game/scenes/SceneLevel.h"

Player::Player (SceneLevel* level, vec2 size) :
    Mob(level, size, Animation(0.25f, {0}, uvec2(96, 96), uvec2(16, 16)))
{}

GameObjectType Player::getType () {
    return GameObjectType::Player;
}

void Player::onStart () {}

void Player::onUpdate (const f32 deltaTime) {
    Mob::onUpdate(deltaTime);
    input();
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