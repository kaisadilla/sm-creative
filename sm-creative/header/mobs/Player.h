#pragma once

#include "root.h"
#include "Mob.h"
#include "../physics/Collider.h"

class Player : public Mob {
private:
    vec2 Ovelocity = vec2(0, 0);
    f32 OminVelocity = 1.f;
    f32 OmaxVelocity = 10.f;
    f32 Oacceleration = 1.f;
    f32 Odrag = 0.98f;

    vec2 velocity = vec2(0, 0);
    f32 minVelocity = 0.1f;
    f32 maxUp = 9.8f * 16.f;
    f32 maxDown = 9.8f * 16.f;
    f32 maxHoriz = 8.f * 16.f;
    f32 gravityPull = 1.f * 16.f;

    Collider collider;

    bool isGrounded = false;

public:
    Player(vec2 size);

    void onUpdate(const f32 deltaTime, const std::vector<Collider>& __testc);

    void move2(const vec2& direction);
    void updatePhysics(const f32 deltaTime);

    inline const Collider& getCollider () const {
        return collider;
    }

private:
    void __input (const f32 deltaTime) {
        f32 amount = 16.f * 8.f * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            amount *= 2.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
            amount = 5.f * deltaTime;
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
            velocity.y = -5.f;
        }
    }
};