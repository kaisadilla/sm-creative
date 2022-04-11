#include "mobs/Enemy.h"
#include "game/scenes/SceneLevel.h"

Enemy::Enemy(SceneLevel* level, vec2 size, AnimationState& animations) :
    Mob(level, size, animations)
{
    sound_stomp.setBuffer(Assets::sound_stomp);
}