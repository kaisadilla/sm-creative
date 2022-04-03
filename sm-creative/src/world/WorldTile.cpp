#include "world/WorldTile.h"

WorldTile::WorldTile () : tile(nullptr) {

}

WorldTile::WorldTile (Tile* tile) : tile(tile) { }

void WorldTile::draw (sf::RenderWindow& window, vec2 position) {
    if (tile != nullptr && !tile->isAirTile()) {
        sf::Sprite& sprite = tile->getSprite();
        sprite.setPosition(vec2(position.x, position.y));
        window.draw(sprite);
    }
}