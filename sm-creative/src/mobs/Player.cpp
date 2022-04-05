#include "mobs/Player.h"

Player::Player (vec2 size) : Mob(size) {}

GameObjectType Player::getType () {
    return GameObjectType::Tile;
}

void Player::onUpdate (const f32 deltaTime) {
    __input();
}

void Player::onFixedUpdate (const f32 fixedTime) {
    updatePhysics(fixedTime);
}

void Player::checkCollisions (const std::vector<Collider>& colliders) {
    bool collided = false;
    isGrounded = false;

    std::vector<const Collider*> secondRound;

    for (const Collider& otherCollider : colliders) {
        Collision collision;
        if (collider.checkColision(otherCollider, collision)) {
            // get whatever we collided with
            IGameObject* cw = otherCollider.getGameObject();
            if (cw->getType() == GameObjectType::Tile) {
                WorldTile* tile = dynamic_cast<WorldTile*>(cw);
            }

            collided = true;

            if (collision.direction == Direction::UP || collision.direction == Direction::DOWN) {
                move(0, collision.intersection.y);
                velocity.y = 0.f;

                if (collision.direction == Direction::DOWN) {
                    isGrounded = true;
                }
            }
            else if (collision.direction == Direction::LEFT || collision.direction == Direction::RIGHT) {
                secondRound.push_back(&otherCollider);
                velocity.x = 0.f;
            }
        }
    }

    for (const Collider* otherCollider : secondRound) {
        Collision collision;
        if (collider.checkColision(*otherCollider, collision)) {
            collided = true;

            if (collision.direction == Direction::LEFT || collision.direction == Direction::RIGHT) {
                move(collision.intersection.x, 0);
            }

            collider.setCenter(position + size / 2.f);
        }
    }

    sprite.setFillColor(collided ? sf::Color::Red : sf::Color::White);
}

void Player::move2 (const vec2& direction) {
    // Accelerate
    //velocity.x += direction.x * acceleration;
    //velocity.y += direction.y * acceleration;

    Ovelocity += direction * Oacceleration;

    // Limit velocity
    Ovelocity.x = std::clamp(Ovelocity.x, -OmaxVelocity, OmaxVelocity);
    Ovelocity.y = std::clamp(Ovelocity.y, -OmaxVelocity, OmaxVelocity);
}

void Player::updatePhysics (const f32 fixedTime) {
    //velocity.y = std::clamp(velocity.y + (1.0f * deltaTime), 0.f, 9.8f);
    velocity.y = std::min(velocity.y + 16.f, 9.8f * 16.f * 4.f);

    // TODO: This needs deltaTime. Inputs will add deltaTime to acceleration, not velocity.
    move(velocity * fixedTime);

    //Ovelocity.x *= Odrag;
    //
    //if (std::abs(Ovelocity.x) < OminVelocity) {
    //    Ovelocity.x = 0.f;
    //}
    //if (std::abs(Ovelocity.y) < OminVelocity) {
    //    Ovelocity.y = 0.f;
    //}
}
