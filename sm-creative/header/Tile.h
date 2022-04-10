#pragma once

#include "root.h"

class Tile {
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
    Tile(const string& internalName, sf::Texture& atlas, i32 spriteIndex);

    static Tile* airTile(string& internalName);

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
    /// Given the direction of the collision by the mob (which is the side of the mob that collided with
    /// the tile, not vice versa), returns true if the block can collide from that direction.
    /// </summary>
    /// <param name="mobSide">The side OF THE MOB that collided with this tile.</param>
    /// <param name="mobVelocity">The velocity of the mob at this moment.</param>
    inline bool hasMobCollided (const Direction mobSide, const vec2& mobVelocity) {
        return (mobSide == Direction::UP && mobVelocity.y < 0.f && collisionDown)
            || (mobSide == Direction::DOWN && mobVelocity.y > 0.f && collisionUp)
            || (mobSide == Direction::LEFT && mobVelocity.x < 0.f && collisionRight)
            || (mobSide == Direction::RIGHT && mobVelocity.x > 0.f && collisionLeft);
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
    Tile();
};