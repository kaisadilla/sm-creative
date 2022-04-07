#include "mobs/Mob.h"

Mob::Mob (vec2 size) : size(size), collider(this, position + size / 2.f, vec2((size.x / 2.f) - 1, size.y / 2.f)) {

}

void Mob::updatePhysics (f32 fixedTime) {
    velocity.y = std::min(velocity.y + 16.f, 9.8f * 16.f * 4.f);

    move(velocity * fixedTime);
}

void Mob::setSprite (const char* path, uvec2 size) {
    texture.loadFromFile(path);

    sprite = sf::RectangleShape(vec2(size.x, size.y));
    sprite.setTexture(&texture);
    sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Mob::checkCollisions (const std::vector<Collider>& colliders) {
    constexpr f32 COLLISION_THRESHOLD = 1.5f;

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

                if (std::abs(collision.intersection.x) > COLLISION_THRESHOLD) {
                    velocity.y = 0.f;

                    if (collision.direction == Direction::DOWN) {
                        isGrounded = true;
                    }
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
                if (std::abs(collision.intersection.y) > COLLISION_THRESHOLD) {
                    move(collision.intersection.x, 0);
                }
            }

            collider.setCenter(position + size / 2.f);
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
