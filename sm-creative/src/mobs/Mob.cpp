#include "mobs/Mob.h"
#include "game/scenes/SceneLevel.h"

Mob::Mob (SceneLevel* level, vec2 size, AnimationState& animations) :
    level(level),
    size(size),
    collider(this),
    animations(animations)
{}

void Mob::updatePhysics () {
    checkLookingLeft();
    velocity.y = std::min(velocity.y + (12.f * gravity), 8.f * 16.f * 4.f);

    move(velocity * SECONDS_PER_FIXED_UPDATE);
}

void Mob::setSprite (const char* path, uvec2 size) {
    texture.loadFromFile(path);

    sprite = sf::RectangleShape(vec2(size.x, size.y));
    sprite.setTexture(&texture);
    sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Mob::jump (f32 strength) {
    velocity.y = -strength;
}

void Mob::die () {
    isDead = true;
}

void Mob::dispose () {
    disposePending = true;
}

void Mob::checkCollisionsWithTiles (const std::vector<Collider>& colliders) {
    constexpr f32 COLLISION_THRESHOLD = 1.5f;

    isGrounded = false;
    std::vector<const Collider*> secondRound;

    for (const Collider& otherCollider : colliders) {
        Collision collision;

        if (collider.checkColision(otherCollider, collision)) {
            if (!isCollisionValid(collision)) continue;

            if (collision.direction == Direction::UP || collision.direction == Direction::DOWN) {
                collided = true;
                if (!ignoresWalls) {
                    if (std::abs(collision.intersection.x) > COLLISION_THRESHOLD) {
                        move(0, collision.intersection.y);
                        velocity.y = 0.f;

                        if (collision.direction == Direction::DOWN) {
                            isGrounded = true;
                        }
                    }
                }

                onCollisionWithTile(collision);
            }
            else if (collision.direction == Direction::LEFT || collision.direction == Direction::RIGHT) {
                secondRound.push_back(&otherCollider);
            }
        }
    }

    for (const Collider* otherCollider : secondRound) {
        Collision collision;

        if (collider.checkColision(*otherCollider, collision)) {
            if (!isCollisionValid(collision)) continue;

            collided = true;
            if (!ignoresWalls) {
                velocity.x = 0.f;

                if (std::abs(collision.intersection.y) > COLLISION_THRESHOLD) {
                    move(collision.intersection.x, 0);
                }
            }

            onCollisionWithTile(collision);
        }
    }

    //if (isGrounded) {
    //    sprite.setFillColor(sf::Color::Green);
    //}
    //else {
    //    sprite.setFillColor(collided ? sf::Color::Red : sf::Color::White);
    //}
}

void Mob::move (vec2 direction) {
    setPosition(vec2(position.x + direction.x, position.y + direction.y));
}

void Mob::move (f32 x, f32 y) {
    setPosition(vec2(position.x + x, position.y + y));
}

void Mob::onUpdate () {
    animations.onUpdate(Time::getDeltaTime(), animationSpeed);
    sprite.setTextureRect(animations.getCurrentAnimation().getCurrentSlice(isLookingLeft && canBeMirrored));
}

void Mob::onFixedUpdate () {
    updatePhysics();
    checkOutOfBounds();
}

void Mob::checkOutOfBounds () {
    if (position.x < -32.f || position.x > level->getWidth() + 32.f) {
        dispose();
    }
    else if (position.y < -240.f || position.y > level->getHeight() + 32.f) {
        dispose();
    }
}

bool Mob::isCollisionValid (const Collision& collision) const {
    WorldTile* tile = (WorldTile*)collision.collider->getGameObject();
    return tile->getTile()->hasMobCollided(collision.direction, velocity);
}

void Mob::checkLookingLeft () {
    // Note that if the horizontal speed is exactly 0, we don't update this value.
    if (velocity.x < 0.f) {
        isLookingLeft = true;
    }
    else if (velocity.x > 0.f) {
        isLookingLeft = false;
    }
}
