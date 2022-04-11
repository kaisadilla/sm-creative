#include "characters/Mob.h"
#include "game/scenes/SceneLevel.h"

Mob::Mob(SceneLevel* level, const vec2& size, AnimationState& animations) :
    Character(level, size, animations)
{
    sound_stomp.setBuffer(Assets::sound_stomp);
}