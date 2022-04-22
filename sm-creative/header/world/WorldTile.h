#pragma once

#include "root.h"
#include "__delete_Tile.h"
#include "physics/IGameObject.h"

class WorldTile : public IGameObject {
private:
    __delete_Tile* tile;

public:
    WorldTile();
    WorldTile(__delete_Tile* tile);

    GameObjectType getType();
    void draw(sf::RenderWindow& window, vec2 position);

    inline __delete_Tile* getTile () {
        return tile;
    }

    inline bool isAirTile () const {
        return tile->isAirTile();
    }
};