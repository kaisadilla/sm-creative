#pragma once

#include "root.h"
#include "SM_Time.h"
#include "animation/AnimationState.h"
#include "assets/Assets.h"
#include "physics/Collider.h"
#include "physics/Collision.h"
#include "physics/IGameObject.h"

class Player;

class Tile : public IGameObject {
    friend class TileReader;

protected:
    /// <summary>
    /// Contains the position of the tile inside the level.
    /// </summary>
    vec2 position;
    /// <summary>
    /// Contains the point in the level in which the tile is drawn, which may or may not correspond
    /// to its actual position in the level.
    /// </summary>
    vec2 drawPosition;

    AnimationState animations;
    sf::Sprite sprite;

    /************
     * COLLIDER *
     ************/
    Collider collider;

public:
    Tile();

    GameObjectType getType() override { return GameObjectType::Tile; }
    
    virtual void onStart();
    virtual void onUpdate();

    virtual bool hasMobCollided(const Collision& collision, const vec2& mobVelocity) const;
    
    /// <summary>
    /// An event that must be called manually by the Player class when necessary.
    /// </summary>
    /// <param name="collision">The collision that triggered this effect.</param>
    /// <param name="player">The player that triggered this effect.</param>
    virtual void onCollisionWithPlayer(Collision& collision, Player* player) {};

public:
    /// <summary>
    /// Returns the position of the tile aligned with the pixel grid.
    /// </summary>
    inline vec2 getDisplayPositionAligned () const {
        return vec2(std::floorf(drawPosition.x), std::floorf(drawPosition.y));
    }

    inline Collider getCollider () const {
        return collider;
    }

    /// <summary>
    /// Sets the position of the tile in the pixel grid.
    /// </summary>
    /// <param name="position">The position of the tile in the pixel grid.</param>
    inline void setPosition (const vec2& position) {
        this->position = position;
        setDrawPosition(position);
    }

    /// <summary>
    /// Sets the position of the tile inside the tile grid.
    /// </summary>
    /// <param name="position">The position of the tile in the tile grid.</param>
    inline void setGridPosition (const ivec2& position) {
        setPosition(vec2(position.x * PIXELS_PER_TILE, position.y * PIXELS_PER_TILE));
    }

    /// <summary>
    /// Sets the position at which to draw the tile in the pixel grid.
    /// </summary>
    /// <param name="displayPosition">The position at which to draw the tile in the pixel grid.</param>
    inline void setDrawPosition (const vec2& displayPosition) {
        this->drawPosition = displayPosition;
        sprite.setPosition(getDisplayPositionAligned());
    }

    /// <summary>
    /// Moves the display position of the tile by the vector given.
    /// </summary>
    /// <param name="x">The x component of the displacement vector.</param>
    /// <param name="y">The y component of the displacement vector.</param>
    inline void moveDrawPosition (const i32 x, const i32 y) {
        setDrawPosition(drawPosition + vec2(x, y));
    }

    /// <summary>
    /// Moves the display position of the tile by the vector given.
    /// </summary>
    /// <param name="vec">The displacement vector.</param>
    inline void moveDrawPosition (const vec2 vec) {
        setDrawPosition(drawPosition + vec);
    }

    /// <summary>
    /// Sets the display position back to the logical position of this tile.
    /// </summary>
    inline void restartDrawPosition () {
        setDrawPosition(position);
    }

    inline void draw (sf::RenderWindow& window) const {
        window.draw(sprite);
    }
};