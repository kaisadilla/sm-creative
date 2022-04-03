#include "world/Level.h"

Level::Level () :
    foregroundPlane(0, 0)
{}

Level::Level (const ui32& width, const ui32& height) :
    foregroundPlane(width, height)
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
            string str_tile = json_level["grid"]["" + std::to_string(x) + "," + std::to_string(y)];
            ui32 index = Assets::__tilePositionMap[str_tile];
            Tile& tile = Assets::tiles[index];

            level->foregroundPlane.setAt(x, y, WorldTile(&tile));
        }
    }

    return level;
}
