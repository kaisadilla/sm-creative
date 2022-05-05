#include "entities/Entity.h"
#include "entities/Enemy.h"
#include "entities/Item.h"
#include "entities/Player.h"
#include "game/scenes/LevelScene.h"
#include "tiles/Tile.h"

Entity::Entity() :
    collider(this)
{}

Entity::~Entity () {
    animations.free();
    std::cout << "Destroyed entity with id " << id << "\n";
}

void Entity::updatePhysics () {
    checkLookingLeft();
    velocity.y = std::min(velocity.y + (12.f * gravityScale), 8.f * 16.f * 4.f);

    move(velocity * SECONDS_PER_FIXED_UPDATE);
}

void Entity::setSprite (const ui32 spriteIndex) {
    const string& texName = Assets::getEntitySpriteAt(spriteIndex);

    texture.loadFromFile("res/sprites/entities/" + texName + ".png");
    sprite = sf::RectangleShape(entitySize);
    sprite.setTexture(&texture);
    sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
}

void Entity::setColliderSize (const sf::IntRect& colliderPosition) {
    vec2 colliderCenter;
    vec2 colliderEdge;
    Collider::calculateVectorsInsideSprite(size, colliderPosition, colliderCenter, colliderEdge);
    collider.setRelativeCenter(colliderCenter);
    collider.setDistanceToEdge(colliderEdge);
}

void Entity::setLevel (LevelScene* level) {
    this->level = level;
}

void Entity::start() {
    onStart();
}

void Entity::update() {
    if (isUpdated) {
        onUpdate();
    }
    if (playingAnimation) {
        if (animGetFromBlock) {
            animGetFromBlock->onUpdate([this](i32 yPos) {
                setPosition(vec2(position.x, yPos));
            });
        }
    }
}

void Entity::fixedUpdate() {
    if (isUpdated) {
        onFixedUpdate();
    }
}

void Entity::initializeDefaultSpriteAndColliderSizes (const vec2& spriteSize, const sf::IntRect& colliderPosition) {
    size = spriteSize;
    sprite.setSize(size);

    defaultCollider = colliderPosition;

    setColliderSize(defaultCollider);
}

void Entity::setDefaultSizes (const vec2& entitySize, const vec2& textureSize, const sf::IntRect& collider) {
    this->entitySize = entitySize;
    this->textureSize = textureSize;
    defaultCollider = collider;

    size = entitySize;
    sprite.setSize(entitySize);

    setColliderSize(defaultCollider);
}

void Entity::jump (f32 strength) {
    velocity.y = -strength;
}

void Entity::die () {
    isDead = true;
}

void Entity::dispose () {
    disposePending = true;
}

void Entity::move (vec2 direction) {
    setPosition(vec2(position.x + direction.x, position.y + direction.y));
}

void Entity::move (f32 x, f32 y) {
    setPosition(vec2(position.x + x, position.y + y));
}

void Entity::onStart () {
}

void Entity::onUpdate () {
    animations.onUpdate(Time::getDeltaTime(), animationSpeed);

    sf::IntRect uvs = animations.getCurrentAnimation().getCurrentSlice(isLookingLeft && flipSpriteWhenLookingLeft);
    if (flipHorizontal) {
        uvs.left += uvs.width;
        uvs.width = -uvs.width;
    }
    if (flipVertical) {
        uvs.top += uvs.height;
        uvs.height = -uvs.height;
    }

    sprite.setTextureRect(uvs);

    if (isDead) {
        despawnTimer -= Time::getDeltaTime();
        if (despawnTimer < 0.f) {
            dispose();
        }
    }
}

void Entity::onFixedUpdate () {
    if (ignoreEntityCollisionTimer > 0.f) {
        ignoreEntityCollisionTimer = std::max(0.f, ignoreEntityCollisionTimer - SECONDS_PER_FIXED_UPDATE);
    }

    updatePhysics();
    checkOutOfBounds();
}

void Entity::checkCollisionWithTiles (const std::vector<std::unique_ptr<Tile>>& tiles, const i32 startingIndex) {
    constexpr f32 COLLISION_THRESHOLD = 1.5f;

    if (ignoresTiles) {
        return;
    }

    isGrounded = false;

    std::vector<i32> secondRound;
    Collision collision;

    for (i32 i = startingIndex; i < tiles.size(); i++) {
        const auto& tile = tiles[i];

        if (collider.checkCollision(tile->getCollider(), collision)) {
            if (!isCollisionValid(collision, *tile)) continue;

            if (collision.direction == Direction::UP || collision.direction == Direction::DOWN) {
                collided = true;

                if (!canGoThroughTiles) {
                    if (std::abs(collision.intersection.x) > COLLISION_THRESHOLD) {
                        move(0, collision.intersection.y);
                        velocity.y = 0.f;

                        if (collision.direction == Direction::DOWN) {
                            isGrounded = true;
                        }
                    }
                }

                onCollisionWithTile(collision, *tile);
            }
            else if (collision.direction == Direction::LEFT || collision.direction == Direction::RIGHT) {
                secondRound.push_back(i);
            }
        }
    }

    for (const i32 i : secondRound) {
        const auto& tile = tiles[i];

        if (collider.checkCollision(tile->getCollider(), collision)) {
            if (!isCollisionValid(collision, *tile)) continue;

            collided = true;
            if (!canGoThroughTiles) {
                velocity.x = 0.f;

                if (std::abs(collision.intersection.y) > COLLISION_THRESHOLD) {
                    move(collision.intersection.x, 0);
                }
            }

            onCollisionWithTile(collision, *tile);
        }
    }
}

void Entity::checkCollisionWithEntities (const std::vector<std::unique_ptr<Entity>>& entities, const i32 startingIndex) {
    if (!collidesWithEntities()) {
        return;
    }

    Collision collision;

    for (i32 i = startingIndex; i < entities.size(); i++) {
        const auto& entity = entities[i];

        if (collider.checkCollision(entity->getCollider(), collision)) {
            if (entity->collidesWithEntities()) {
                this->triggerCollisionWithEntityEvent(collision, entity.get());
                entity->triggerCollisionWithEntityEvent(collision, this);
            }
        }
    }
}

void Entity::playGetFromBlockAnimation () {
    auto& tween = tweeny::uptrFrom(position.y);
    tween->to(position.y - 16).during(750);

    animGetFromBlock = std::make_unique<TweenAnimation<f32>>();
    animGetFromBlock->setTween(tween);
    animGetFromBlock->setEndCallback([this]() {
        drawBeforeForeground = false;
        playingAnimation = false;
        isUpdated = true;
        animGetFromBlock.reset();
    });
    animGetFromBlock->start();

    isUpdated = false;
    playingAnimation = true;
    drawBeforeForeground = true;
}

void Entity::checkOutOfBounds () {
    if (position.x < -32.f || position.x > level->getPixelWidth() + 32.f) {
        dispose();
    }
    else if (position.y < -240.f || position.y > level->getPixelHeight() + 32.f) {
        dispose();
    }
}

bool Entity::isCollisionValid (const Collision& collision, const Tile& tile) const {
    return tile.hasMobCollided(collision, velocity);
}

void Entity::checkLookingLeft () {
    // Note that if the horizontal speed is exactly 0, we don't update this value.
    if (velocity.x < 0.f) {
        isLookingLeft = true;
    }
    else if (velocity.x > 0.f) {
        isLookingLeft = false;
    }
}

void Entity::triggerCollisionWithEntityEvent (Collision& collision, Entity* entity) {
    if (entity->getType() == GameObjectType::Enemy) {
        if (!this->ignoresMobs && !entity->ignoresMobs) {
            onCollisionWithEnemy(collision, dynamic_cast<Enemy*>(entity));
        }
    }
    else if (entity->getType() == GameObjectType::Item) {
        onCollisionWithItem(collision, dynamic_cast<Item*>(entity));
    }
    else if (entity->getType() == GameObjectType::Player) {
        onCollisionWithPlayer(collision, dynamic_cast<Player*>(entity));
    }
}

void Entity::__TEMPORARY_set_sprite_by_filename (const char* name, vec2 size) {
    texture.loadFromFile(string("res/sprites/entities/") + name + string(".png"));

    sprite = sf::RectangleShape(vec2(size.x, size.y));
    sprite.setTexture(&texture);
    sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}