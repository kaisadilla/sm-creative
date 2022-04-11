#include "characters/Goomba.h"
#include "characters/Player.h"
#include "game/scenes/SceneLevel.h"

Goomba::Goomba(SceneLevel* level, vec2 size, bool startingDirectionRight) :
    Mob(
        level,
        size,
        AnimationState({
            Animation(0.2f, {0, 1}, uvec2(3, 1), uvec2(16, 16)),
            Animation(5.f , {2}   , uvec2(3, 1), uvec2(16, 16)),
        })
    ),
    startingDirectionRight(startingDirectionRight)
{
    vec2 colliderCenter;
    vec2 colliderEdge;
    Collider::calculateVectorsInsideSprite(size, sf::IntRect(0, 0, 16, 16), colliderCenter, colliderEdge);
    collider.setCenter(colliderCenter);
    collider.setDistanceToEdge(colliderEdge);
}

GameObjectType Goomba::getType() {
    return GameObjectType::Enemy;
}

void Goomba::onStart () {
    velocity.x = (startingDirectionRight ? SPEED : -SPEED);
}

void Goomba::onUpdate () {
    Character::onUpdate();
}

void Goomba::onCollisionWithTile (Collision& collision) {
    if (collision.direction == Direction::LEFT) {
        velocity.x = SPEED;
    }
    else if (collision.direction == Direction::RIGHT) {
        velocity.x = -SPEED;
    }
}

void Goomba::onCollisionWithPlayer (Player& player) {
    if (!isDead) {
        if (player.getPosition().y < position.y - 2) {
            die();
            sound_stomp.play();
            player.jump(16.f * 16.f);
        }
        else {
            player.die();
        }
    }
}

void Goomba::die () {
    Character::die();
    animations.setState(AnimStates::Goomba::DEAD);
    velocity.x = 0;

    JobManager::addJob(.25f, [this]() {
        dispose();
    });
}