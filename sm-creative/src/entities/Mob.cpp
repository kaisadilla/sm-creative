#include "entities/Mob.h"

void Mob::checkCollisionWithEnemies (const std::vector<Mob*>& enemies, int start) {
    if (collidesWithEntities()) {
        Collision collision;
        
        for (i32 i = start; i < enemies.size(); i++) {
            const auto& enemy = enemies[i];

            if (collider.checkColision(enemy->getCollider(), collision)) {
                if (enemy->collidesWithEntities()) {
                    // two ifs because the "ignoresMobs" properties could change
                    // after each collision event.
                    if (!this->ignoresMobs && !enemy->ignoresMobs) {
                        this->onCollisionWithMob(collision, enemy);
                    }
                    if (!this->ignoresMobs && !enemy->ignoresMobs) {
                        enemy->onCollisionWithMob(collision, this);
                    }
                }
            }
        }
    }
}

void Mob::onUpdate () {
    Entity::onUpdate();
}

void Mob::dieWithStyle (Direction direction) {
    dyingWithStyle = true;
    isDead = true;
    despawnTimer = 3.f;

    ignoresTiles = true;
    ignoresMobs = true;

    velocity.x = (direction == Direction::LEFT) ? 16.f * -4.f : 16.f * 4.f;
    velocity.y = 16.f * -14.f;
    animationSpeed = 0.f;
    flipVertical = true;

    sound_kick.play();
}

bool Mob::isBeingTrampledByPlayer(const sf::FloatRect& playerCollider) {
    return (playerCollider.top + playerCollider.height) < (getColliderPosition().top + 4);
}
