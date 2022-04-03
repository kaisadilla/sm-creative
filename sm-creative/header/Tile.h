#pragma once

#include "root.h"

class Tile {
private:
    bool _isAirTile = false;
    string internalName;
    sf::Sprite sprite;

public:
    Tile(const string& internalName, sf::Texture& atlas, i32 spriteIndex);

    static Tile* airTile(string& internalName);

    inline sf::Sprite& getSprite () {
        return sprite;
    }

    inline bool isAirTile () const {
        return _isAirTile;
    }

private:
    Tile();
};