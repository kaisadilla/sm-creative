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
    avoidsCliffs(avoidsCliffs),
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

    debug_checkedCliffTile.setFillColor(sf::Color(255, 0, 0, 128));
    debug_checkedCliffTile.setSize(vec2(16.f, 16.f));
}

void Goomba::onUpdate () {
    Character::onUpdate();

    if (avoidsCliffs) {
        checkCliffs();
    }
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
    animations.setState(AnimStates::DEAD);
    velocity.x = 0;

    JobManager::addJob(.25f, [this]() {
        dispose();
    });
}

void Goomba::drawDebugInfo (sf::RenderWindow& window) {
    if (avoidsCliffs) {
        debug_checkedCliffTile.setPosition(vec2(checkedCliffTile.x * 16.f, checkedCliffTile.y * 16.f));
        window.draw(debug_checkedCliffTile);
    }
}

void Goomba::checkCliffs () {
    const ivec2& gridPos = getGridPosition();

    if (velocity.x < 0.f) {
        checkedCliffTile = ivec2(gridPos.x, gridPos.y + 1);
    }
    else if (velocity.x > 0.f) {
        checkedCliffTile = ivec2(gridPos.x + 1, gridPos.y + 1);
    }

    const WorldTile* tileAtLeft = level->getTileAt(checkedCliffTile.x, checkedCliffTile.y);
    if (tileAtLeft == nullptr || tileAtLeft->isAirTile()) {
        velocity.x = SPEED;
    }
}
