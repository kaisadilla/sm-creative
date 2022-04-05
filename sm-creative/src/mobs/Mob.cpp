#include "mobs/Mob.h"

Mob::Mob (vec2 size) : size(size), collider(this, position + size / 2.f, vec2((size.x / 2.f) - 1, size.y / 2.f)) {

}

void Mob::move (vec2 direction) {
    setPosition(vec2(position.x + direction.x, position.y + direction.y));
}

void Mob::move (f32 x, f32 y) {
    setPosition(vec2(position.x + x, position.y + y));
}
