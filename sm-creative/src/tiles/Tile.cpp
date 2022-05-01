#include "tiles/Tile.h"
#include "assets/Assets.h"

Tile::Tile () {
    sprite.setTexture(Assets::tileAtlas);
}

void Tile::setLevel(LevelScene* level) {
    this->level = level;
}

void Tile::onStart () {
    sprite.setTextureRect(animations.getCurrentAnimation().getCurrentSlice(false));
}

void Tile::onUpdate () {
    animations.onUpdate(Time::getDeltaTime(), 1.f);
    sprite.setTextureRect(animations.getCurrentAnimation().getCurrentSlice(false));
}

bool Tile::hasMobCollided (const Collision& collision, const vec2& mobVelocity) const {
    return true;
}
