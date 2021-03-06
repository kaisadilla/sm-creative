#include "entities/SuperMushroom.h"
#include "entities/Player.h"

SuperMushroom::SuperMushroom ()
{
    flipSpriteWhenLookingLeft = false;
    gravityScale = 0.f;
}

void SuperMushroom::onStart () {
    Item::onStart();

    velocity.x = (startingDirectionRight ? SPEED_X : -SPEED_X);
}

void SuperMushroom::onUpdate () {
    Item::onUpdate();
}

void SuperMushroom::onCollisionWithTile (Collision& collision, Tile& tile) {
    if (collision.direction == Direction::LEFT) {
        velocity.x = SPEED_X;
    }
    else if (collision.direction == Direction::RIGHT) {
        velocity.x = -SPEED_X;
    }
}

void SuperMushroom::onCollisionWithPlayer (Collision& collision, Player* player) {
    isDead = true;
    despawnTimer = 0.f;
    player->setMode(Player::MarioMode::BIG);
}

void SuperMushroom::updatePhysics () {
    velocity.y = SPEED_Y;

    move(velocity * SECONDS_PER_FIXED_UPDATE);
}