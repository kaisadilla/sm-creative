#include "vfx/Particle.h"

void Particle::onStart () {
    sprite.setTextureRect(animation->getCurrentSlice(false));
}

void Particle::onUpdate () {
    animation->onUpdate(Time::getDeltaTime(), animationSpeed);
    sprite.setTextureRect(animation->getCurrentSlice(false));
}

void Particle::destroy () {
    disposePending = true;
}
