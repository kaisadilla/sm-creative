#include "characters/Koopa.h"
#include "characters/Player.h"
#include "game/scenes/SceneLevel.h"

Koopa::Koopa(SceneLevel* level, const vec2& size, const sf::IntRect& shellCollider, bool avoidsCliffs, bool startingDirectionRight, bool canRevive) :
    Mob(
        level,
        size,
        AnimationState({
            Animation(0.2f, {0, 1}   , uvec2(6, 1), uvec2(18, 27)), // walking
            Animation(60.f, {2}      , uvec2(6, 1), uvec2(18, 27)), // shell
            Animation(0.03f, {2, 3, 4}, uvec2(6, 1), uvec2(18, 27)), // shell travelling
            Animation(0.1f, {2, 5}   , uvec2(6, 1), uvec2(18, 27)), // shell reanimating
            Animation(60.f, {2}      , uvec2(6, 1), uvec2(18, 27))  // dead
        })
    ),
    IAvoidCliffs(avoidsCliffs, size.y),
    shellCollider(shellCollider),
    startingDirectionRight(startingDirectionRight),
    canRevive(canRevive)
{
    sound_kick.setBuffer(Assets::sound_kick);
}

void Koopa::onStart () {
    Mob::onStart();
    IAvoidCliffs::onStart();

    velocity.x = (startingDirectionRight ? WALKING_SPEED : -WALKING_SPEED);
}

void Koopa::onUpdate () {
    Mob::onUpdate();

    if (isReviving) {
        animationSpeed = 1.f + (std::powf(1 - secondsUntilReviveEnd, 2) * 3.f);
    }
    else {
        animationSpeed = 1.f;
    }
}

void Koopa::onFixedUpdate () {
    Mob::onFixedUpdate();

    if (avoidsCliffs && !isShell) {
        checkCliffs(this, WALKING_SPEED);
    }
    checkShellRevive();
}

void Koopa::onCollisionWithTile (Collision& collision) {
    if (collision.direction == Direction::LEFT) {
        velocity.x = isShell ? SHELL_SPEED : WALKING_SPEED;
    }
    else if (collision.direction == Direction::RIGHT) {
        velocity.x = isShell ? -SHELL_SPEED : -WALKING_SPEED;
    }
}

void Koopa::onCollisionWithMob (Collision& collision, Mob* mob) {
    if (isShell) {
        if (std::abs(velocity.x) > 0.1f) {
            mob->takeDamage(true);
        }
    }
    else {
        if (collision.getDirectionForGameObject(this) == Direction::LEFT) {
            velocity.x = -WALKING_SPEED;
        }
        else if (collision.getDirectionForGameObject(this) == Direction::RIGHT) {
            velocity.x = WALKING_SPEED;
        }
    }
}

void Koopa::onCollisionWithPlayer (Collision& collision, Player& player) {
    if (!isDead) {
        if (isShell) {
            if (std::abs(velocity.x) < 0.1f) {
                pushShell(collision.horizontalDirection, collision.intersection.x);
            }
            else {
                if (player.getPosition().y < position.y - 2) {
                    stopShell();
                    player.jump(16.f * 16.f);
                }
                else {
                    player.takeDamage(false);
                }
            }
        }
        else {
            if (player.getPosition().y < position.y - 2) {
                if (canRevive) {
                    takeDamage(false);
                    player.jump(16.f * 16.f);
                }
                else {
                    die();
                }
                sound_stomp.play();
                player.jump(16.f * 16.f);
            }
            else {
                player.takeDamage(false);
            }
        }
    }
}

void Koopa::takeDamage (bool forceDeath) {
    turnIntoShell();
}

void Koopa::die () {
    Mob::die();
    animations.setState(AnimStates::Koopa::DEAD);
    velocity.x = 0;

    JobManager::addJob(.25f, [this]() {
        dispose();
    });
}

void Koopa::turnIntoShell () {
    isShell = true;

    secondsUntilReviveStart = 6.f;
    velocity.x = 0;
    setColliderSize(shellCollider);
    animations.setState(AnimStates::Koopa::SHELL);
}

void Koopa::checkShellRevive () {
    if (isShell && velocity.x == 0.f) {
        if (isReviving == false) {
            secondsUntilReviveStart -= SECONDS_PER_FIXED_UPDATE;

            if (secondsUntilReviveStart <= 0.f) {
                startRevive();
            }
        }
        else {
            secondsUntilReviveEnd -= SECONDS_PER_FIXED_UPDATE;

            if (secondsUntilReviveEnd <= 0.f) {
                revive();
            }
        }
    }
}

void Koopa::startRevive () {
    isReviving = true;
    secondsUntilReviveEnd = 1.f;
    animations.setState(AnimStates::Koopa::SHELL_REANIMATING);
}

void Koopa::revive () {
    isShell = false;
    isReviving = false;

    velocity.x = isLookingLeft ? -WALKING_SPEED : WALKING_SPEED;
    setColliderSize(defaultCollider);
    animations.setState(AnimStates::Koopa::WALKING);
}

void Koopa::pushShell (Direction direction, f32 push) {
    constexpr f32 EXTRA_PUSH = 0.01f;

    if (direction == Direction::LEFT) {
        move(-push - EXTRA_PUSH, 0);
        velocity.x = -SHELL_SPEED;
    }
    else if (direction == Direction::RIGHT) {
        move(-push + EXTRA_PUSH, 0);
        velocity.x = SHELL_SPEED;
    }
    else {
        return;
    }

    isReviving = false;
    animations.setState(AnimStates::Koopa::SHELL_TRAVELLING);
    sound_kick.play();
}

void Koopa::stopShell () {
    secondsUntilReviveStart = 6.f;
    velocity.x = 0;
    animations.setState(AnimStates::Koopa::SHELL);
}

void Koopa::drawDebugInfo (sf::RenderWindow& window) {
    drawDebugInfo_cliffDetection(window);
}
