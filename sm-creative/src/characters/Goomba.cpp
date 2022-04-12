#include "characters/Goomba.h"
#include "characters/Player.h"
#include "game/scenes/SceneLevel.h"

Goomba::Goomba(SceneLevel* level, const vec2& size, bool avoidsCliffs, bool startingDirectionRight) :
    Mob(
        level,
        size,
        AnimationState({
            Animation(0.2f, {0, 1}, uvec2(3, 1), uvec2(16, 16)),
            Animation(5.f , {2}   , uvec2(3, 1), uvec2(16, 16)),
        })
    ),
    IAvoidCliffs(avoidsCliffs, size.y),
    startingDirectionRight(startingDirectionRight)
{}

void Goomba::onStart () {
    Mob::onStart();
    IAvoidCliffs::onStart();

    velocity.x = (startingDirectionRight ? WALKING_SPEED : -WALKING_SPEED);
}

void Goomba::onUpdate () {
    Mob::onUpdate();
}

void Goomba::onFixedUpdate () {
    Mob::onFixedUpdate();

    if (avoidsCliffs) {
        checkCliffs(this, WALKING_SPEED);
    }
}

void Goomba::onCollisionWithTile (Collision& collision) {
    if (collision.direction == Direction::LEFT) {
        velocity.x = WALKING_SPEED;
    }
    else if (collision.direction == Direction::RIGHT) {
        velocity.x = -WALKING_SPEED;
    }
}

void Goomba::onCollisionWithMob (Collision& collision, Mob* mob) {
    if (collision.getDirectionForGameObject(this) == Direction::LEFT) {
        velocity.x = -WALKING_SPEED;
    }
    else if (collision.getDirectionForGameObject(this) == Direction::RIGHT) {
        velocity.x = WALKING_SPEED;
    }
}

void Goomba::onCollisionWithPlayer (Collision& collision, Player& player) {
    if (!isDead) {
        if (player.getPosition().y < position.y - 2) {
            takeDamage(false);
            sound_stomp.play();
            player.jump(16.f * 16.f);
        }
        else {
            player.takeDamage(false);
        }
    }
}

void Goomba::takeDamage (bool forceDeath) {
    if (forceDeath) {
        dieWithStyle();
    }
    else {
        animations.setState(AnimStates::Goomba::STOMPED);
        velocity.x = 0;

        isDead = true;
        despawnTimer = DEAD_ENEMY_DESPAWN_TIME;
    }
}

void Goomba::die () {
    Mob::die();
    animations.setState(AnimStates::Goomba::STOMPED);
    velocity.x = 0;

    JobManager::addJob(.25f, [this]() {
        dispose();
    });
}

void Goomba::drawDebugInfo (sf::RenderWindow& window) {
    drawDebugInfo_cliffDetection(window);
}