#pragma once

#include <SFML/Audio.hpp>

#include "root.h"
#include "SM_Time.h"
#include "assets/Assets.h"
#include "animation/AnimationState.h"
#include "physics/Collider.h"
#include "physics/IGameObject.h"
#include "world/WorldTile.h"

class LevelScene;
class Item;
class Mob;
class Player;
class Tile;

class Entity : public IGameObject {
    friend class EntityReader;

protected:
    i32 id = -1;
    vec2 position;
    vec2 size;

    /********
     * DATA *
     ********/
    vec2 entitySize;
    vec2 textureSize;
    sf::IntRect defaultCollider;

    /*********
     * STATE *
     *********/
    bool isDead = false;
    f32 despawnTimer = 0.f;
    bool disposePending = false;

    bool collided = false;
    bool isGrounded = false;
    bool isLookingLeft = false;

    /****************************
     * MOVEMENT AND INTERACTION *
     ****************************/
    /// <summary>
    /// The level scene this entity is currently in.
    /// </summary>
    LevelScene* level = nullptr;
    /// <summary>
    /// If true, the entity won't be pushed out of solid tiles when it collides with them.
    /// If the entity has gravity, this means it will fall through the floor.
    /// </summary>
    bool canGoThroughTiles = false;
    /// <summary>
    /// If true, this entity doesn't check collisions with tiles.
    /// </summary>
    bool ignoresTiles = false;
    /// <summary>
    /// If true, this entity doesn't check collisions with mobs.
    /// </summary>
    bool ignoresMobs = false;
    /// <summary>
    /// If true, the entity will be destroyed if it leaves its level's boundaries.
    /// </summary>
    bool destroyWhenOutOfBounds = true;
    /// <summary>
    /// If true, the sprite of this entity will be flipped horizontally when it's looking to the left.
    /// </summary>
    bool flipSpriteWhenLookingLeft = true;

    /***********
     * PHYSICS *
     ***********/
    vec2 velocity = vec2(0, 0);
    f32 gravityScale = 1.f;

    /**********
     * SPRITE *
     **********/
    AnimationState animations;
    sf::Texture texture;
    sf::RectangleShape sprite; // TODO: Replace with sf::Sprite
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

    /************
     * COLLIDER *
     ************/
    Collider collider;
    /// <summary>
    /// If this value is greater than zero, collisions with entities are ignored.
    /// </summary>
    f32 ignoreEntityCollisionTimer = 0.f;

public:
    Entity();
    ~Entity();

    /******************
     * INITIALIZATION *
     ******************/
    void setDefaultSizes(const vec2& entitySize, const vec2& textureSize, const sf::IntRect& collider);
    void setSprite(const ui32 spriteIndex);
    void setColliderSize(const sf::IntRect& colliderPosition); // TODO: Rename to setColliderPosition.
    void setLevel(LevelScene* level);

    /**********
     * EVENTS *
     **********/
    virtual void onStart() {};
    virtual void onUpdate();
    virtual void onFixedUpdate();

    /***********
     * PHYSICS *
     ***********/
    virtual void updatePhysics();
    void move(vec2 direction);
    void move(f32 x, f32 y);
    void checkCollisionWithTiles (const std::vector<std::unique_ptr<Tile>>& tiles, const i32 startingIndex = 0);
    void checkCollisionWithEntities (const std::vector<std::unique_ptr<Entity>>& entities, const i32 startingIndex = 0);

    // remove:

    /// <summary>
    /// Changes the sizes of this entity's sprite and collider. The values given
    /// are set up as its default values.
    /// </summary>
    /// <param name="spriteSize">The size of the sprite, in pixels.</param>
    /// <param name="colliderPosition">The position of the collider relative to the sprite.</param>
    void initializeDefaultSpriteAndColliderSizes(const vec2& spriteSize, const sf::IntRect& colliderPosition); // TODO: DELETE

    virtual void jump(f32 strength);
    virtual void takeDamage(bool forceDeath, Direction direction = Direction::NONE) = 0;
    virtual void die();
    virtual void dispose();
    virtual void checkOutOfBounds();

    virtual void drawDebugInfo(sf::RenderWindow& window) {};

protected:
    bool isCollisionValid(const Collision& collision, const Tile& tile) const;

    virtual void onCollisionWithTile(Collision& collision, Tile& tile) {};
    virtual void onCollisionWithItem(Collision& collision, Item* item) {};
    virtual void onCollisionWithEnemy(Collision& collision, Mob* enemy) {};
    virtual void onCollisionWithPlayer(Collision& collision, Player* player) {};

    virtual void checkLookingLeft();

private:
    /// <summary>
    /// Triggers the onCollision event appropriate for the type of entity given,
    /// verifying first that the collision should be triggered for that type of entity.
    /// </summary>
    /// <param name="collision">The collision that will trigger this event.</param>
    /// <param name="entity">The entity this one collided with.</param>
    void triggerCollisionWithEntityEvent(Collision& collision, Entity* entity);

public:
    void __TEMPORARY_set_sprite_by_filename(const char* name, vec2 size);

public:
    inline i32 getId () const {
        return id;
    }

    inline void setId (i32 id) {
        this->id = id;
    }

    /// <summary>
    /// Returns true if this entity is marked to be deleted.
    /// </summary>
    inline bool getDisposePending () {
        return disposePending;
    }

    /// <summary>
    /// Returns the exact position of the entity inside the level.
    /// </summary>
    inline vec2 getPosition () const {
        return position;
    }

    inline sf::FloatRect getColliderPosition () const {
        return collider.getAbsoluteBounds();
    }

    /// <summary>
    /// Returns the position of the entity aligned with the pixel grid.
    /// </summary>
    inline vec2 getPixelPosition () const {
        return vec2((f32)(i32)position.x, (f32)(i32)position.y);
    }

    /// <summary>
    /// Returns the position the entity is currently in within the level's tile grid.
    /// </summary>
    /// <returns></returns>
    inline ivec2 getGridPosition () const {
        return ivec2((i32)std::floorf(position.x / 16.f), (i32)std::floorf(position.y / 16.f));
    }

    /// <summary>
    /// For the tile cell the entity is currently in, returns its offset (in pixels) from the cell's top-left corner.
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
        return !isDead && ignoreEntityCollisionTimer <= 0.f;
    }

    inline void setPosition (const vec2& position) {
        this->position = position;
        collider.setPosition(position);
        sprite.setPosition(getPixelPosition() + vec2(0, 1));
    }

    inline void setGridPosition (const ivec2& position) {
        setPosition(vec2(position.x * PIXELS_PER_TILE, position.y * PIXELS_PER_TILE));
    }

    inline void draw (sf::RenderWindow& window) const {
        window.draw(sprite);
    }
};