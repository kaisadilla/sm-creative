#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "root.h"
#include "Tile.h"
#include "utils/files.h"

namespace fs = std::filesystem;

class Assets {
    typedef nlohmann::json json;

public:
    inline static sf::Texture tilesAtlas;
    inline static std::vector<Tile> tiles;
    inline static i32 texturesPerRow;
    inline static f32 normalizedTextureSize;
    inline static std::unordered_map<string, i32> __tilePositionMap;

private:
    inline static std::unordered_map<string, i32> tileMap;

public:
    static void loadData () {
        tiles = std::vector<Tile>();
        buildTileAtlas();
        loadTileData();
    }
private:
    static void buildTileAtlas();
    static void loadTileData();
};