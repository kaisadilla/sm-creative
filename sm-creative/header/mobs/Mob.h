#pragma once

#include "root.h"
#include "physics/Collider.h"
#include "physics/IGameObject.h"
#include "world/WorldTile.h"

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
    sf::Texture texture;
    sf::RectangleShape sprite;

    // Movement and interaction.
    Collider collider;
    bool isGrounded = false;
    vec2 velocity = vec2(0, 0);

public:
    Mob(vec2 size);

    void setSprite(const char* path, uvec2 size);

    void move(vec2 direction);
    void move(f32 x, f32 y);
    virtual void updatePhysics(f32 fixedTime);
    virtual void checkCollisions(const std::vector<Collider>& colliders);

    inline vec2 getPosition () {
        return position;
    }

    /// <summary>
    /// Returns the position the mob is currently in within the level's tile grid.
    /// </summary>
    /// <returns></returns>
    inline ivec2 getGridPosition () {
        return ivec2(position.x / 16, position.y / 16);
    }

    /// <summary>
    /// For the tile cell the mob is currently in, returns its offset (in pixels) from the cell's top-left corner.
    /// </summary>
    inline ivec2 getGridPositionOffset () {
        return ivec2((int)position.x & 0xf, (int)position.y & 0xf);
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