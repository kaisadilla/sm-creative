#pragma once

#include "root.h"
#include "SM_Time.h"
#include "animation/StaticAnimation.h"
#include "animation/DynamicAnimation.h"
#include "physics/Collider.h"
#include "physics/Collision.h"
#include "physics/IGameObject.h"

class Player;

class Tile : public IGameObject {
    friend class TileReader;

protected:
    vec2 position;
    std::unique_ptr<SpriteAnimation> animation;
    sf::Sprite sprite;

    /************
     * COLLIDER *
     ************/
    Collider collider;

public:
    Tile();

    GameObjectType getType() override { return GameObjectType::Tile; }
    
    void onUpdate();

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
    inline vec2 getPixelPosition () const {
        return vec2(std::floorf(position.x), std::floorf(position.y));
    }

    inline Collider getCollider () const {
        return collider;
    }

    inline void setPosition (const vec2& position) {
        this->position = position;
        sprite.setPosition(getPixelPosition());
    }

    inline void setGridPosition (const ivec2& position) {
        setPosition(vec2(position.x * PIXELS_PER_TILE, position.y * PIXELS_PER_TILE));
    }

    inline void draw (sf::RenderWindow& window) const {
        window.draw(sprite);
    }

protected:
    inline void setAnimation (std::unique_ptr<SpriteAnimation>& animation) {
        this->animation = std::move(animation);
        sprite.setTextureRect(this->animation->getCurrentSlice(false));
    }
};