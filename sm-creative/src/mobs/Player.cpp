#include "mobs/Player.h"
#include "mobs/Enemy.h"
#include "game/scenes/SceneLevel.h"

Player::Player (SceneLevel* level, vec2 size) :
    Mob(
        level,
        size,
        AnimationState({
            Animation(60.f, {0}   , uvec2(6, 6), uvec2(16, 16)),
            Animation(0.1f, {0, 1}, uvec2(6, 6), uvec2(16, 16)),
            Animation(60.f, {4}   , uvec2(6, 6), uvec2(16, 16)),
        })
    )
{
    destroyWhenOutOfBounds = false;
}

GameObjectType Player::getType () {
    return GameObjectType::Player;
}

void Player::onStart () {}

void Player::onUpdate (const f32 deltaTime) {
    Mob::onUpdate(deltaTime);
    input(deltaTime);
    setAnimationState();
}

void Player::onFixedUpdate (const f32 fixedTime) {
    Mob::onFixedUpdate(fixedTime);
    checkLevelBoundaries();
}

void Player::input (const f32 deltaTime) {
    f32 acc = ACCELERATION_X * deltaTime;
    f32 maxSpeed = MAX_SPEED_X;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        acc *= 2.f;
        maxSpeed *= 2.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
        maxSpeed = 2.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        velocity.x = std::fmaxf(-maxSpeed, velocity.x - acc);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        velocity.x = std::fminf(maxSpeed, velocity.x + acc);
    }
    else {
        velocity.x = 0;
    }

    if (isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        jump(32.f * 16.f);
    }
}

void Player::checkCollisionWithEnemies (const std::vector<Enemy*>& enemies) {
    Collision collision;
    for (const auto& enemy : enemies) {
        if (collider.checkColision(enemy->getCollider(), collision)) {
            enemy->onCollisionWithPlayer(*this);
        }
    }
}

void Player::killPlayer () {
    isDead = true;
}

void Player::setAnimationState () {
    if (isDead) {
        animations.setState(AnimStates::Player::DEAD);
    }
    else {
        if (velocity.x == 0) {
            animations.setState(AnimStates::Player::STILL);
        }
        else {
            animations.setState(AnimStates::Player::WALKING);
        }
    }
}

void Player::checkLevelBoundaries () {
    if (position.x < 0) {
        position.x = 0;
    }
    else if (position.x > level->getWidth() - size.y) {
        position.x = level->getWidth() - size.y;
    }
}
