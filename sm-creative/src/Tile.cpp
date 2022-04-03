#include "Tile.h"

Tile::Tile () {}

Tile::Tile (const string& internalName, sf::Texture& atlas, i32 spriteIndex) : internalName(internalName) {
    sprite.setTexture(atlas);

    i32 y = (spriteIndex / 24) * 16;
    i32 x = (spriteIndex % 24) * 16;

    sprite.setTextureRect(sf::IntRect(x, y, 16, 16));
}

Tile* Tile::airTile(string& internalName) {
    Tile* tile = new Tile();
    tile->internalName = internalName;
    tile->_isAirTile = true;
    return tile;
}
