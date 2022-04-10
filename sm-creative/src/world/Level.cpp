#include "world/Level.h"

Level::Level () :
    width(0),
    height(0),
    backgroundLayer(0, 0),
    foregroundLayer(0, 0)
{}

Level::Level (const ui32 width, const ui32 height) :
    width(width),
    height(height),
    backgroundLayer(width, height),
    foregroundLayer(width, height)
{}

Level* Level::loadFromFile (const char* path) {
    string str_tiles = utils::readTextFile(path);
    json json_level = json::parse(str_tiles);

    auto width2 = json_level["width"];

    const ui32 width = json_level["width"];
    const ui32 height = json_level["height"];

    Level* level = new Level(width, height);

    for (ui32 x = 0; x < width; x++) {
        for (ui32 y = 0; y < height; y++) {
            string str_tile = json_level["grids"]["background"]["" + std::to_string(x) + "," + std::to_string(y)];
            ui32 index = Assets::__tilePositionMap[str_tile];
            Tile& tile = Assets::tiles[index];

            level->backgroundLayer.setAt(x, y, WorldTile(&tile));
        }
    }

    for (ui32 x = 0; x < width; x++) {
        for (ui32 y = 0; y < height; y++) {
            string str_tile = json_level["grids"]["foreground"]["" + std::to_string(x) + "," + std::to_string(y)];
            ui32 index = Assets::__tilePositionMap[str_tile];
            Tile& tile = Assets::tiles[index];

            level->foregroundLayer.setAt(x, y, WorldTile(&tile));
        }
    }

    return level;
}
