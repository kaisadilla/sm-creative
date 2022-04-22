#pragma once

#include "root.h"
#include "physics/Collision.h"

class __delete_Tile {
    friend class Assets;

private:
    bool _isAirTile = false;
    string internalName;
    sf::Sprite sprite;

    bool collisionUp = true;
    bool collisionDown = true;
    bool collisionLeft = true;
    bool collisionRight = true;

public:
    __delete_Tile(const string& internalName, sf::Texture& atlas, i32 spriteIndex);

    static __delete_Tile* airTile(string& internalName);

    inline const string& getInternalName () const {
        return internalName;
    }

    inline sf::Sprite& getSprite () {
        return sprite;
    }

    inline bool isAirTile () const {
        return _isAirTile;
    }

    inline bool hasCollider () const {
        return collisionUp || collisionDown || collisionLeft || collisionRight;
    }

    /// <summary>
    /// Given the direction of the collision by the character (which is the side of the character
    /// that collided with the tile, not vice versa), returns true if the block can collide from that direction.
    /// </summary>
    /// <param name="collision">The collision of the character with this tile.</param>
    /// <param name="mobVelocity">The velocity of the character at this moment.</param>
    inline bool hasMobCollided (const Collision& collision, const vec2& mobVelocity) {
        return (collision.direction == Direction::UP    && mobVelocity.y < 0.f && collisionDown )
            || (collision.direction == Direction::DOWN  && mobVelocity.y > 0.f && collisionUp   )
            || (collision.direction == Direction::LEFT  && mobVelocity.x < 0.f && collisionRight)
            || (collision.direction == Direction::RIGHT && mobVelocity.x > 0.f && collisionLeft );
        //return (collision.direction == Direction::UP    && mobVelocity.y < 0.f && collisionDown  && collision.intersection.y < +4.f)
        //    || (collision.direction == Direction::DOWN  && mobVelocity.y > 0.f && collisionUp    && collision.intersection.y > -4.f)
        //    || (collision.direction == Direction::LEFT  && mobVelocity.x < 0.f && collisionRight && collision.intersection.x < +4.f)
        //    || (collision.direction == Direction::RIGHT && mobVelocity.x > 0.f && collisionLeft  && collision.intersection.x > -4.f);
    }

    inline bool hasColliderFromTop () {
        return collisionUp;
    }

    inline bool hasColliderFromBottom () {
        return collisionDown;
    }

    inline bool hasColliderFromLeft () {
        return collisionLeft;
    }

    inline bool hasColliderFromRight () {
        return collisionRight;
    }

private:
    __delete_Tile();
};