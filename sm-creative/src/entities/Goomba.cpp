#include "entities/Goomba.h"
#include "entities/Player.h"
#include "game/scenes/SceneLevel.h"

Goomba::Goomba(bool avoidsCliffs, bool startingDirectionRight) :
    IAvoidCliffs(avoidsCliffs, size.y), // TODO: Size is not yet defined at this point.
    startingDirectionRight(startingDirectionRight)
{}

void Goomba::initializeAnimations () {
    DynamicAnimation* aWalking = new DynamicAnimation({ 3, 1 }, textureSize, 0.2f, { 0, 1 });
    StaticAnimation*  aStomped = new StaticAnimation({ 3, 1 }, textureSize, 2);

    animations.setAnimations({
        aWalking,
        aStomped
    });
}

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

    if (!dyingWithStyle && avoidsCliffs) {
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
        if (isBeingTrampledByPlayer(player.getColliderPosition())) {
            takeDamage(false);
            sound_stomp.play();
            player.jump(16.f * 16.f);
        }
        else {
            player.takeDamage(false);
        }
    }
}

void Goomba::takeDamage (bool forceDeath, Direction direction) {
    if (forceDeath) {
        dieWithStyle(direction);
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