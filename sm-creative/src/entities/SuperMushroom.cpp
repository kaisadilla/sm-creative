#include "entities/SuperMushroom.h"
#include "entities/Player.h"

SuperMushroom::SuperMushroom (bool startingDirectionRight) :
    startingDirectionRight(startingDirectionRight)
{
    flipSpriteWhenLookingLeft = false;
    gravityScale = 0.f;
}

void SuperMushroom::initializeAnimations () {
    StaticAnimation* anim = new StaticAnimation({ 1, 1 }, textureSize, 0);

    animations.setAnimations({
        anim
    });
}

void SuperMushroom::onStart () {
    Item::onStart();

    velocity.x = (startingDirectionRight ? SPEED_X : -SPEED_Y);
}

void SuperMushroom::onUpdate () {
    Item::onUpdate();
}

void SuperMushroom::onCollisionWithTile (Collision& collision) {
    if (collision.direction == Direction::LEFT) {
        velocity.x = SPEED_X;
    }
    else if (collision.direction == Direction::RIGHT) {
        velocity.x = -SPEED_X;
    }
}

void SuperMushroom::onCollisionWithPlayer (Collision& collision, Player& player) {
    isDead = true;
    despawnTimer = 0.f;
    player.setMode(Player::MarioMode::BIG);
}

void SuperMushroom::updatePhysics () {
    velocity.y = SPEED_Y;

    move(velocity * SECONDS_PER_FIXED_UPDATE);
}