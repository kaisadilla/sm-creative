#include "characters/Character.h"
#include "game/scenes/SceneLevel.h"

Character::Character (SceneLevel* level, vec2 size, AnimationState& animations) :
    level(level),
    size(size),
    collider(this),
    animations(animations)
{}

void Character::updatePhysics () {
    checkLookingLeft();
    velocity.y = std::min(velocity.y + (12.f * gravity), 8.f * 16.f * 4.f);

    move(velocity * SECONDS_PER_FIXED_UPDATE);
}

void Character::setSprite (const char* name, vec2 size) {
    texture.loadFromFile(string("res/sprites/characters/") + name + string(".png"));

    sprite = sf::RectangleShape(vec2(size.x, size.y));
    sprite.setTexture(&texture);
    sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Character::setSpriteAndColliderSizes (const vec2& spriteSize, const sf::IntRect& colliderPosition) {
    vec2 colliderCenter;
    vec2 colliderEdge;
    Collider::calculateVectorsInsideSprite(spriteSize, colliderPosition, colliderCenter, colliderEdge);
    collider.setCenter(colliderCenter);
    collider.setCenter(colliderEdge);

    size = spriteSize;
    sprite.setSize(size);
}

void Character::jump (f32 strength) {
    velocity.y = -strength;
}

void Character::die () {
    isDead = true;
}

void Character::dispose () {
    disposePending = true;
}

void Character::checkCollisionsWithTiles (const std::vector<Collider>& colliders) {
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

void Character::move (vec2 direction) {
    setPosition(vec2(position.x + direction.x, position.y + direction.y));
}

void Character::move (f32 x, f32 y) {
    setPosition(vec2(position.x + x, position.y + y));
}

void Character::onUpdate () {
    animations.onUpdate(Time::getDeltaTime(), animationSpeed);
    sprite.setTextureRect(animations.getCurrentAnimation().getCurrentSlice(isLookingLeft && canBeMirrored));
}

void Character::onFixedUpdate () {
    updatePhysics();
    checkOutOfBounds();
}

void Character::checkOutOfBounds () {
    if (position.x < -32.f || position.x > level->getWidth() + 32.f) {
        dispose();
    }
    else if (position.y < -240.f || position.y > level->getHeight() + 32.f) {
        dispose();
    }
}

bool Character::isCollisionValid (const Collision& collision) const {
    WorldTile* tile = (WorldTile*)collision.collider->getGameObject();
    return tile->getTile()->hasMobCollided(collision, velocity);
}

void Character::checkLookingLeft () {
    // Note that if the horizontal speed is exactly 0, we don't update this value.
    if (velocity.x < 0.f) {
        isLookingLeft = true;
    }
    else if (velocity.x > 0.f) {
        isLookingLeft = false;
    }
}