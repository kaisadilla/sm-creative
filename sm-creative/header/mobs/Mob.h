#pragma once

#include "root.h"
#include "Animation.h"
#include "physics/Collider.h"
#include "physics/IGameObject.h"
#include "world/WorldTile.h"

class SceneLevel;

class Mob : public IGameObject {
protected:
    /// <summary>
    /// The position of the mob inside the level, in pixels.
    /// </summary>
    vec2 position;
    /// <summary>
    /// The size of the mob, in pixels.
    /// </summary>
    vec2 size;
    //uvec2 size;
    Animation animation;
    sf::Texture texture;
    sf::RectangleShape sprite;

    // Movement and interaction.
    SceneLevel* level;
    Collider collider;

    vec2 velocity = vec2(0, 0);
    f32 gravity = 1.f;
    /// <summary>
    /// If true, the mob will not collide with any tiles.
    /// If the mob has gravity, this means it will fall through
    /// the floor.
    /// </summary>
    bool ignoresWalls = false;

    bool collided = false;
    bool isGrounded = false;

public:
    Mob(SceneLevel* level, vec2 size, Animation& animation);

    void setSprite(const char* path, uvec2 size);

    void move(vec2 direction);
    void move(f32 x, f32 y);
    virtual void updatePhysics(f32 fixedTime);
    virtual void checkCollisions(const std::vector<Collider>& colliders);

    virtual void onStart() {};
    virtual void onUpdate(const f32 deltaTime);
    virtual void onFixedUpdate(const f32 fixedTime);

    virtual void onCollision(Collision& collision) {};

    inline vec2 getPosition () const {
        return position;
    }

    /// <summary>
    /// Returns the position the mob is currently in within the level's tile grid.
    /// </summary>
    /// <returns></returns>
    inline ivec2 getGridPosition () const {
        return ivec2(position.x / 16, position.y / 16);
    }

    /// <summary>
    /// For the tile cell the mob is currently in, returns its offset (in pixels) from the cell's top-left corner.
    /// </summary>
    inline ivec2 getGridPositionOffset () const {
        return ivec2((int)position.x & 0xf, (int)position.y & 0xf);
    }

    inline const Collider& getCollider () const {
        return collider;
    }

    inline void setPosition (const vec2& position) {
        this->position = position;
        collider.setCenter(position + size / 2.f);
        sprite.setPosition(position + vec2(0, 1));
    }

    inline void setX (const f32 x) {
        position.x = x;
        collider.setCenter(position + size / 2.f);
        sprite.setPosition(position + vec2(0, 1));
    }

    inline void setY (const f32 y) {
        position.y = y;
        collider.setCenter(position + size / 2.f);
        sprite.setPosition(position + vec2(0, 1));
    }

    inline void draw (sf::RenderWindow& window) const {
        window.draw(sprite);
    }
};