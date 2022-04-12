#include "characters/Mob.h"
#include "game/scenes/SceneLevel.h"

Mob::Mob(SceneLevel* level, const vec2& size, AnimationState& animations) :
    Entity(level, size, animations)
{
    sound_stomp.setBuffer(Assets::sound_stomp);
}

void Mob::checkCollisionWithEnemies (const std::vector<Mob*>& enemies, int start) {
    if (collidesWithEntities()) {
        Collision collision;
        
        for (i32 i = start; i < enemies.size(); i++) {
            const auto& enemy = enemies[i];

            if (collider.checkColision(enemy->getCollider(), collision)) {
                if (enemy->collidesWithEntities()) {
                    this->onCollisionWithMob(collision, enemy);
                    enemy->onCollisionWithMob(collision, this);
                }
            }
        }
    }
}

void Mob::onUpdate () {
    Entity::onUpdate();

    if (isDead) {
        despawnTimer -= Time::getDeltaTime();
        if (despawnTimer < 0.f) {
            dispose();
        }
    }
}

void Mob::dieWithStyle () {
}
