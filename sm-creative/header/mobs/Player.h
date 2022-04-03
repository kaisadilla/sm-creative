#pragma once

#include "root.h"
#include "Mob.h"
#include "../game/Collider.h"

class Player : public Mob {
private:
    vec2 velocity = vec2(0, 0);
    f32 minVelocity = 1.f;
    f32 maxVelocity = 10.f;
    f32 acceleration = 1.f;
    f32 drag = 0.98f;

    Collider collider;

public:
    void __input (f32 deltaTime) {
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
            move(-amount, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            //sprite.move(vec2(128.f * deltaTime, 0));
            //setPosition(vec2(position.x + amount, position.y));
            move(amount, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            //sprite.move(vec2(0, -128.f * deltaTime));
            //setPosition(vec2(position.x, position.y - amount));
            move(0, -amount);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            //sprite.move(vec2(0, 128.f * deltaTime));
            //setPosition(vec2(position.x, position.y + amount));
            move(0, amount);
        }
    }

public:
    Player(vec2 size);

    void onUpdate(const f32 deltaTime, const std::vector<Collider>& __testc);

    void move2(const vec2& direction);
    void updatePhysics(const f32 deltaTime);

    inline const Collider& getCollider () const {
        return collider;
    }
};