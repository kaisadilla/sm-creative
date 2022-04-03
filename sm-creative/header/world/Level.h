#pragma once

#include <nlohmann/json.hpp>

#include "root.h"
#include "world/WorldTile.h"
#include "utils/files.h"
#include "Assets.h"

class Level {
    typedef nlohmann::json json;

private:
    Grid2<WorldTile> foregroundPlane;

public:
    Level();
    Level(const ui32& width, const ui32& height);

    static Level* loadFromFile(const char* path);

    inline const Grid2<WorldTile>& getForegroundPlane () const {
        return foregroundPlane;
    }

    inline ui32 getLevelWidth () const {
        return foregroundPlane.getWidth();
    }

    inline ui32 getLevelHeight () const {
        return foregroundPlane.getHeight();
    }
};