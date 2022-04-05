#pragma once

#include "root.h"
#include "physics/Collider.h"
#include "physics/IGameObject.h"

class Mob : public IGameObject {
    friend class Player;

private:
    /// <summary>
    /// The position of the mob inside the level, in pixels.
    /// </summary>
    vec2 position;
    /// <summary>
    /// The size of the mob, in pixels.
    /// </summary>
    vec2 size;
    //uvec2 size;
    sf::RectangleShape sprite;

    // Movement and interaction.
    Collider collider;
    vec2 velocity = vec2(0, 0);

public:
    Mob(vec2 size);

    void move(vec2 direction);
    void move(f32 x, f32 y);

    inline vec2 getPosition () {
        return position;
    }

    inline void setTexture (const sf::Texture& texture) {
        sprite = sf::RectangleShape(vec2(16.f, 16.f));
        sprite.setTexture(&texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

        position = vec2(2.f, 26.f);
    }

    inline void setPosition (const vec2& position) {
        this->position = position;
        collider.setCenter(position + size / 2.f);
    }

    inline void setX (const f32 x) {
        position.x = x;
        collider.setCenter(position + size / 2.f);
    }

    inline void setY (const f32 y) {
        position.y = y;
        collider.setCenter(position + size / 2.f);
    }

    inline void draw (sf::RenderWindow& window, vec2 offset) {
        sprite.setPosition(vec2(position.x, position.y) - offset);
        window.draw(sprite);
    }
};