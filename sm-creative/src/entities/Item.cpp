#include "entities/Item.h"

Item::Item (SceneLevel* level, const vec2& size, AnimationState& animations) :
    Entity(level, size, animations)
{}

void Item::takeDamage (bool forceDeath, Direction direction) {

}
