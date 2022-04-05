#pragma once

#include "root.h"
#include "Mob.h"
#include "world/WorldTile.h"

class Player : public Mob {
private:
    vec2 Ovelocity = vec2(0, 0);
    f32 OminVelocity = 1.f;
    f32 OmaxVelocity = 10.f;
    f32 Oacceleration = 1.f;
    f32 Odrag = 0.98f;

    f32 minVelocity = 0.1f;
    f32 maxUp = 9.8f * 16.f;
    f32 maxDown = 9.8f * 16.f;
    f32 maxHoriz = 8.f * 16.f;
    f32 gravityPull = 1.f * 16.f;

    bool isGrounded = false;

public:
    Player(vec2 size);

    GameObjectType getType();

    void onUpdate(const f32 deltaTime);
    void onFixedUpdate(const f32 fixedTime);
    void checkCollisions(const std::vector<Collider>& colliders);

    void move2(const vec2& direction);
    void updatePhysics(const f32 fixedTime);

    inline const Collider& getCollider () const {
        return collider;
    }

private:
    void __input () {
        f32 amount = 16.f * 8.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            amount *= 2.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
            amount = 5.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            //sprite.move(vec2(-128.f * deltaTime, 0));
            //setPosition(vec2(position.x - amount, position.y));
            //move(-amount, 0);
            velocity.x = -amount;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            //sprite.move(vec2(128.f * deltaTime, 0));
            //setPosition(vec2(position.x + amount, position.y));
            //move(amount, 0);
            velocity.x = amount;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            //sprite.move(vec2(0, -128.f * deltaTime));
            //setPosition(vec2(position.x, position.y - amount));
            //move(0, -amount);
            velocity.y = -amount;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            //sprite.move(vec2(0, 128.f * deltaTime));
            //setPosition(vec2(position.x, position.y + amount));
            //move(0, amount);
            velocity.y = amount;
        }
        if (isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            velocity.y = -40.f * 16.f;
        }
    }
};