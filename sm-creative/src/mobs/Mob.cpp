#include "mobs/Mob.h"
#include "game/scenes/SceneLevel.h"

Mob::Mob (SceneLevel* level, vec2 size, AnimationState& animations) :
    level(level),
    size(size),
    collider(this, position + size / 2.f, vec2((size.x / 2.f) - 1, size.y / 2.f)),
    animations(animations)
{}

void Mob::updatePhysics (f32 fixedTime) {
    velocity.y = std::min(velocity.y + (16.f * gravity), 9.8f * 16.f * 4.f);

    move(velocity * fixedTime);
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

void Mob::checkCollisionsWithTiles (const std::vector<Collider>& colliders) {
    constexpr f32 COLLISION_THRESHOLD = 1.5f;

    isGrounded = false;

    std::vector<const Collider*> secondRound;

    for (const Collider& otherCollider : colliders) {
        Collision collision;

        if (collider.checkColision(otherCollider, collision)) {
            if (collision.direction == Direction::UP || collision.direction == Direction::DOWN) {
                collided = true;

                if (!ignoresWalls) {
                    move(0, collision.intersection.y);

                    if (std::abs(collision.intersection.x) > COLLISION_THRESHOLD) {
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

void Mob::onUpdate (const f32 deltaTime) {
    animations.onUpdate(deltaTime, animationSpeed);
    sprite.setTextureRect(animations.getCurrentAnimation().getCurrentSlice());
}

void Mob::onFixedUpdate (const f32 fixedTime) {
    updatePhysics(fixedTime);
    checkOutOfBounds();
}

void Mob::checkOutOfBounds () {
    if (position.x < -1.f || position.x > level->getWidth() + 1.f) {
        // TODO: Destroy.
    }
    if (position.y < -10.f || position.y > level->getHeight() + 1.f) {
        // TODO: Destroy.
    }
}
