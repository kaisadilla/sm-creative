#include "tiles/Tile.h"
#include "assets/Assets.h"

Tile::Tile () {
    sprite.setTexture(Assets::tileAtlas);
}

void Tile::onUpdate () {
    animation->onUpdate(Time::getDeltaTime(), 1.f);
    sprite.setTextureRect(animation->getCurrentSlice(false));
}