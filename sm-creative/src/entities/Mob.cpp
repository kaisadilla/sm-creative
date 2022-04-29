#include "entities/Mob.h"

Mob::Mob () {
    sound_stomp.setBuffer(Assets::sound_stomp);
    sound_kick.setBuffer(Assets::sound_kick);
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
