#pragma once

#include "root.h"
#include "Tile.h"

class WorldTile {
private:
    Tile* tile;

public:
    WorldTile();
    WorldTile(Tile* tile);

    void draw (sf::RenderWindow& window, vec2 position);

    inline Tile* getTile () {
        return tile;
    }
};