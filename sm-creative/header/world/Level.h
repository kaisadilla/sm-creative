#pragma once

#include <nlohmann/json.hpp>

#include "root.h"
#include "world/WorldTile.h"
#include "utils/files.h"

class Level {
    typedef nlohmann::json json;

private:
    Grid2<WorldTile> foregroundPlane;

public:
    Level();
    Level(const ui32& width, const ui32& height);

    inline const Grid2<WorldTile>& getForegroundPlane () const {
        return foregroundPlane;
    }

    void __debug_build_plane () {
        for (ui32 x = 0; x < foregroundPlane.getWidth(); x++) {
            for (ui32 y = 0; y < foregroundPlane.getHeight(); y++) {
                if (y == 17) {
                    foregroundPlane.setAt(x, y, WorldTile(&Assets::tiles[x % (Assets::tiles.size() - 1)]));
                }
                else {
                    foregroundPlane.setAt(x, y, WorldTile(&Assets::tiles[0]));
                }
            }
        }
    }

    void __build_level_from_json (const char* path) {
        string str_tiles = utils::readTextFile(path);
        json json_level = json::parse(str_tiles);

        auto width2 = json_level["width"];

        const ui32 width = json_level["width"];
        const ui32 height = json_level["height"];

        foregroundPlane = Grid2<WorldTile>(width, height);

        for (ui32 x = 0; x < width; x++) {
            for (ui32 y = 0; y < height; y++) {
                string str_tile = json_level["grid"]["" + std::to_string(x) + "," + std::to_string(y)];
                ui32 index = Assets::__tilePositionMap[str_tile];
                Tile& tile = Assets::tiles[index];

                foregroundPlane.setAt(x, y, WorldTile(&tile));
            }
        }
    }

    inline ui32 getLevelWidth () const {
        return foregroundPlane.getWidth();
    }

    inline ui32 getLevelHeight () const {
        return foregroundPlane.getHeight();
    }
};