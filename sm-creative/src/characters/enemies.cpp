#include "characters/enemies.h"
#include "game/scenes/SceneLevel.h"

Mob* createEnemyForLevel (data::WorldMob mobData, SceneLevel* level) {
    const i32& id = mobData.getId();
    const vec2& size = mobData.getSpriteDimensions();
    const sf::IntRect& defaultCollider = mobData.getCollider("collider");
    const vec2& position = mobData.getPosition();

    Mob* enemy = nullptr;

    if (mobData.getBehavior() == data::Behavior::Goomba) {
        bool avoidsCliffs = mobData.getBehaviorProperty<bool>("avoidsCliffs");
        bool startingDirectionRight = mobData.getBehaviorProperty<bool>("startingDirectionRight");

        enemy = new Goomba(level, size, avoidsCliffs, startingDirectionRight);
    }
    else if (mobData.getBehavior() == data::Behavior::Koopa) {
        sf::IntRect shellCollider = mobData.getCollider("shellCollider");
        bool avoidsCliffs = mobData.getBehaviorProperty<bool>("avoidsCliffs");
        bool startingDirectionRight = mobData.getBehaviorProperty<bool>("startingDirectionRight");
        bool canRevive = mobData.getBehaviorProperty<bool>("canRevive");

        enemy = new Koopa(level, size, shellCollider, avoidsCliffs, startingDirectionRight, canRevive);
    }
    else {
        std::cout << "[Error] Can't create mob with id " << id << "\n";
        return nullptr;
    }

    enemy->setId(id);
    enemy->setSprite(mobData.getSprite().c_str(), size);
    enemy->initializeDefaultSpriteAndColliderSizes(size, defaultCollider);
    enemy->setPosition(vec2(position.x * 16.f, position.y * 16.f));

    std::cout << "Generated enemy of type " << (int)mobData.getBehavior() << " with id " << id << "\n";

    return enemy;
}
