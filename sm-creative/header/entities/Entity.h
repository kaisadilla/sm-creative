#pragma once

#include <SFML/Audio.hpp>

#include "root.h"
#include "SM_Time.h"
#include "animation/AnimationState.h"
#include "physics/Collider.h"
#include "physics/IGameObject.h"
#include "world/WorldTile.h"

class SceneLevel;
class Player;

class Entity : public IGameObject {
protected:
    i32 id = -1;
    /// <summary>
    /// The position of the mob inside the level, in pixels.
    /// </summary>
    vec2 position;
    /// <summary>
    /// The size of the mob, in pixels.
    /// </summary>
    vec2 size;
    bool flipSpriteWhenLookingLeft = true;

    /*********
     * STATE *
     *********/
    bool isDead = false;
    f32 despawnTimer = 0.f;
    bool disposePending = false;

    /**********
     * SPRITE *
     **********/
    AnimationState animations;
    sf::Texture texture;
    sf::RectangleShape sprite;
    f32 animationSpeed = 1.f;
    /// <summary>
    /// If true, the sprite will be rendered flipped horizontally.
    /// </summary>
    bool flipHorizontal = false;
    /// <summary>
    /// If true, the sprite will be rendered flipped vertically.
    /// </summary>
    bool flipVertical = false;
    /// <summary>
    /// True if this entity is playing a transitional animation.
    /// </summary>
    bool playingTransitionalAnimation = false;
    /// <summary>
    /// An animation that overrides the normal animations of this entity.
    /// This is used, for example, when Mario picks up a mushroom and displays
    /// a "growing" animation before he becomes Big Mario.
    /// </summary>
    DynamicAnimation* transitionalAnimation = nullptr;

    /****************************
     * MOVEMENT AND INTERACTION *
     ****************************/
    sf::IntRect defaultCollider;
    /// <summary>
    /// If true, the mob won't be pushed out of solid tiles when it collides with them.
    /// If the mob has gravity, this means it will fall through the floor.
    /// </summary>
    bool canGoThroughTiles = false;
    /// <summary>
    /// If true, this mob doesn't check collisions with tiles.
    /// </summary>
    bool ignoresTiles = false;
    /// <summary>
    /// If true, this mob doesn't check collisions with mobs.
    /// </summary>
    bool ignoresMobs = false;
    /// <summary>
    /// If true, the mob will be destroyed if it leaves its level's boundaries.
    /// </summary>
    bool destroyWhenOutOfBounds = true;

    SceneLevel* level;
    Collider collider;

    vec2 velocity = vec2(0, 0);
    f32 gravityScale = 1.f;

    bool collided = false;
    bool isGrounded = false;
    bool isLookingLeft = false;

    /// <summary>
    /// If this value is greater than zero, collisions with entities are ignored.
    /// </summary>
    f32 ignoreEntityCollisionTimer = 0.f;

public:
    Entity(SceneLevel* level, vec2 size, AnimationState& animation);
    ~Entity();

    /// <summary>
    /// Changes the sizes of this mob's sprite and collider. The values given
    /// are set up as its default values.
    /// </summary>
    /// <param name="spriteSize">The size of the sprite, in pixels.</param>
    /// <param name="colliderPosition">The position of the collider relative to the sprite.</param>
    void initializeDefaultSpriteAndColliderSizes(const vec2& spriteSize, const sf::IntRect& colliderPosition);

    void setSprite(const char* name, vec2 size);
    void setColliderSize(const sf::IntRect& colliderPosition);

    void move(vec2 direction);
    void move(f32 x, f32 y);
    virtual void updatePhysics();
    virtual void checkCollisionsWithTiles(const std::vector<Collider>& colliders);

    virtual void jump(f32 strength);
    virtual void takeDamage(bool forceDeath, Direction direction = Direction::NONE) = 0;
    virtual void die();
    virtual void dispose();

    virtual void onStart() {};
    virtual void onUpdate();
    virtual void onFixedUpdate();

    virtual void onCollisionWithTile(Collision& collision) {};
    virtual void onCollisionWithPlayer(Collision& collision, Player& player) {};
    virtual void checkOutOfBounds();

    virtual void drawDebugInfo(sf::RenderWindow& window) {};

protected:
    bool isCollisionValid(const Collision& collision) const;
    virtual void checkLookingLeft();

public:
    inline i32 getId () const {
        return id;
    }

    inline void setId (i32 id) {
        this->id = id;
    }

    /// <summary>
    /// Returns true if this mob is marked to be deleted.
    /// </summary>
    inline bool getDisposePending () {
        return disposePending;
    }

    /// <summary>
    /// Returns the exact position of the mob inside the level.
    /// </summary>
    inline vec2 getPosition () const {
        return position;
    }

    inline sf::FloatRect getColliderPosition () const {
        return collider.getAbsoluteBounds();
    }

    /// <summary>
    /// Returns the position of the mob aligned with the pixel grid.
    /// </summary>
    inline vec2 getPixelPosition () const {
        return vec2((f32)(i32)position.x, (f32)(i32)position.y);
    }

    /// <summary>
    /// Returns the position the mob is currently in within the level's tile grid.
    /// </summary>
    /// <returns></returns>
    inline ivec2 getGridPosition () const {
        return ivec2((i32)std::floorf(position.x / 16.f), (i32)std::floorf(position.y / 16.f));
    }

    /// <summary>
    /// For the tile cell the mob is currently in, returns its offset (in pixels) from the cell's top-left corner.
    /// </summary>
    inline ivec2 getGridPositionOffset () const {
        return ivec2((i32)position.x & 0xf, (i32)position.y & 0xf);
    }

    inline bool getLookingLeft () const {
        return isLookingLeft;
    }

    inline const Collider& getCollider () const {
        return collider;
    }

    inline bool collidesWithEntities () {
        return ignoreEntityCollisionTimer <= 0.f;
    }

    inline void setPosition (const vec2& position) {
        this->position = position;
        collider.setPosition(position);
        sprite.setPosition(getPixelPosition() + vec2(0, 1));
    }

    inline void draw (sf::RenderWindow& window) const {
        window.draw(sprite);
    }
};