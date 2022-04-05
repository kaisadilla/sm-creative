#pragma once

#include "root.h"
#include "Tile.h"
#include "physics/IGameObject.h"

class WorldTile : public IGameObject {
private:
    Tile* tile;

public:
    WorldTile();
    WorldTile(Tile* tile);

    GameObjectType getType();
    void draw(sf::RenderWindow& window, vec2 position);

    inline Tile* getTile () {
        return tile;
    }
};