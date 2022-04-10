#include "mobs/Goomba.h"
#include "mobs/Player.h"
#include "game/scenes/SceneLevel.h"

Goomba::Goomba(SceneLevel* level, vec2 size, bool startingDirectionRight) :
    Enemy(
        level,
        size,
        AnimationState({
            Animation(0.2f, {0, 1}, uvec2(3, 1), uvec2(16, 16)),
            Animation(5.f , {2}   , uvec2(3, 1), uvec2(16, 16)),
        })
    ),
    startingDirectionRight(startingDirectionRight)
{}

GameObjectType Goomba::getType() {
    return GameObjectType::Enemy;
}

void Goomba::onStart () {
    velocity.x = (startingDirectionRight ? SPEED : -SPEED);
}

void Goomba::onUpdate () {
    Mob::onUpdate();
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
            player.jump(16.f * 16.f);
        }
        else {
            player.die();
        }
    }
}

void Goomba::die () {
    Mob::die();
    animations.setState(AnimStates::Goomba::DEAD);
    velocity.x = 0;

    // TODO: Actually disappear
    Job job(2.f, []() {std::cout << "Coming Soon: Goomba dies." << "\n"; });
    JobManager::addJob(job);
}