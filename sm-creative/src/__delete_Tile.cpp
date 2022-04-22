#include "__delete_Tile.h"

__delete_Tile::__delete_Tile () {}

__delete_Tile::__delete_Tile (const string& internalName, sf::Texture& atlas, i32 spriteIndex) : internalName(internalName) {
    sprite.setTexture(atlas);

    i32 y = (spriteIndex / 24) * 16;
    i32 x = (spriteIndex % 24) * 16;

    sprite.setTextureRect(sf::IntRect(x, y, 16, 16));
}

__delete_Tile* __delete_Tile::airTile(string& internalName) {
    __delete_Tile* tile = new __delete_Tile();
    tile->internalName = internalName;
    tile->_isAirTile = true;
    tile->collisionUp = false;
    tile->collisionDown = false;
    tile->collisionLeft = false;
    tile->collisionRight = false;
    return tile;
}