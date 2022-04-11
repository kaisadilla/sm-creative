#include "characters/Player.h"
#include "characters/Mob.h"
#include "game/scenes/SceneLevel.h"

Player::Player (SceneLevel* level, vec2 size) :
    Character(
        level,
        size,
        AnimationState({
            Animation(60.f, {0}   , uvec2(6, 6), uvec2(16, 16)),
            Animation(0.1f, {0, 1}, uvec2(6, 6), uvec2(16, 16)),
            Animation(60.f, {3}   , uvec2(6, 6), uvec2(16, 16)),
            Animation(60.f, {2}   , uvec2(6, 6), uvec2(16, 16)),
            Animation(60.f, {4}   , uvec2(6, 6), uvec2(16, 16)),
        })
    )
{
    vec2 colliderCenter;
    vec2 colliderEdge;
    Collider::calculateVectorsInsideSprite(size, sf::IntRect(3, 1, 10, 15), colliderCenter, colliderEdge);
    collider.setCenter(colliderCenter);
    collider.setDistanceToEdge(colliderEdge);

    destroyWhenOutOfBounds = false;
    sound_jump.setBuffer(Assets::sound_jump);
    //sound_jump.setVolume(50.f);
}

GameObjectType Player::getType () {
    return GameObjectType::Player;
}

void Player::onStart () {}

void Player::onUpdate () {
    Character::onUpdate();
    input();
    setAnimationState();
}

void Player::onFixedUpdate () {
    Character::onFixedUpdate();
    checkLevelBoundaries();
}

void Player::onCollisionWithTile (Collision& collision) {
    if (collision.direction == Direction::UP) {
        playerJumpEnd(true);
    }
}

void Player::input () {
    f32 acc = ACCELERATION_X * Time::getDeltaTime();
    f32 maxSpeed = MAX_SPEED_X;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        maxSpeed *= 1.555f; // Original goes to 18 to 28, which is ~1.5555555555-.
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
        maxSpeed = 2.f;
    }
    if (!isGrounded) {
        acc *= 0.75f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        if (velocity.x > 0.f) {
            acc *= 2.f;
        }
        velocity.x = std::fmaxf(-maxSpeed, velocity.x - acc);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        if (velocity.x < 0.f) {
            acc *= 2.f;
        }
        velocity.x = std::fminf(maxSpeed, velocity.x + acc);
    }
    else {
        if (isGrounded) {
            // Start losing speed if the player is moving, or stop completely when below 0.1 abs horizontal speed.
            if (velocity.x < 0.1f) {
                velocity.x = std::fminf(0.f, velocity.x + (ACCELERATION_X * Time::getDeltaTime()));
            }
            else if (velocity.x > 0.1f) {
                velocity.x = std::fmaxf(0.f, velocity.x - (ACCELERATION_X * Time::getDeltaTime()));
            }
            else {
                velocity.x = 0.f;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
        if (isJumping) {
            playerJump();
        }
        else if (!isJumping && isGrounded) {
            playerJumpStart();
        }
    }
    else if (isJumping) {
        playerJumpEnd(false);
    }
}

void Player::playerJumpStart () {
    jumpStart = Time::getTime();
    jumpTime = 0.f;
    jumpMinTime = 0.08f;
    jumpMaxTime = 0.4f;
    isJumping = true;

    sound_jump.play();

    gravity = 0.f;
    playerJump();
}

void Player::playerJump () {
    if (isJumping) {
        jumpTime += Time::getDeltaTime();
        if (jumpTime > jumpMaxTime) {
            playerJumpEnd(false);
        }
        else {
            velocity.y = (-16.f * 4.f) / 0.4f;
        }
    }
}

void Player::playerJumpEnd (bool forced) {
    if (isJumping) {
        if (!forced && jumpTime < jumpMinTime) {
            playerJump();
        }
        else {
            gravity = 1.f;
            isJumping = false;
            jumpTime = 0.f;
        }
    }
}

void Player::checkCollisionWithEnemies (const std::vector<Mob*>& enemies) {
    Collision collision;
    for (const auto& enemy : enemies) {
        if (collider.checkColision(enemy->getCollider(), collision)) {
            enemy->onCollisionWithPlayer(*this);
        }
    }
}

void Player::die () {
    Character::die();
}

void Player::setAnimationState () {
    animationSpeed = 1.f;
    if (isDead) {
        animations.setState(AnimStates::Player::DEAD);
    }
    else {
        if (isGrounded) {
            if (velocity.x == 0) {
                animations.setState(AnimStates::Player::STILL);
            }
            else if (velocity.x < 0.f) {
                // if the player is moving left but pressing right, it is skidding.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                    animations.setState(AnimStates::Player::SKID);
                }
                else {
                    animationSpeed = std::abs(velocity.x / 64.f);
                    animations.setState(AnimStates::Player::WALKING);
                }
            }
            else if (velocity.x > 0.f) {
                // if the player is moving right but pressing left, it is skidding.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    animations.setState(AnimStates::Player::SKID);
                }
                else {
                    animationSpeed = std::abs(velocity.x / 64.f);
                    animations.setState(AnimStates::Player::WALKING);
                }
            }
        }
        else {
            animations.setState(AnimStates::Player::JUMPING);
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

void Player::checkLookingLeft () {
    Character::checkLookingLeft();

    // TODO: This could probably be simplified as "the player is always looking in the direction he's pressing".
    // when skidding, the player is looking at the direction he's trying to move in.
    if (velocity.x < 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        isLookingLeft = false;
    }
    else if (velocity.x > 0.f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        isLookingLeft = true;
    }

    // when airborne, the player is looking at the direction he's trying to look in.
    if (!isGrounded) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            isLookingLeft = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            isLookingLeft = false;
        }
    }
}
