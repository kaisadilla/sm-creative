#pragma once

#include <nlohmann/json.hpp>

#include "root.h"
#include "world/WorldTile.h"
#include "utils/files.h"
#include "Assets.h"

class Level {
    typedef nlohmann::json json;

private:
    ui32 width;
    ui32 height;
    Grid2<WorldTile> backgroundLayer;
    Grid2<WorldTile> foregroundLayer;

public:
    Level();
    Level(const ui32 width, const ui32 height);

    static Level* loadFromFile(const char* path);

    inline ui32 getWidth () const {
        return width;
    }

    inline ui32 getHeight () const {
        return height;
    }

    inline const Grid2<WorldTile>& getBackgroundLayer () const {
        return backgroundLayer;
    }

    inline const Grid2<WorldTile>& getForegroundLayer () const {
        return foregroundLayer;
    }
};