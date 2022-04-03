#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "root.h"
#include "Tile.h"
#include "utils/files.h"
#include "world/Level.h"

namespace fs = std::filesystem;

class Level;

class Assets {
    typedef nlohmann::json json;

public:
    inline static sf::Texture tilesAtlas;
    inline static std::vector<Tile> tiles;
    inline static i32 texturesPerRow;
    inline static f32 normalizedTextureSize;
    inline static std::unordered_map<string, i32> __tilePositionMap;
    inline static std::unordered_map<string, Level> levels;

private:
    inline static std::unordered_map<string, i32> tileMap;

public:
    static void loadData () {
        tiles = std::vector<Tile>();
        buildTileAtlas();
        loadTileData();
        loadLevels();
    }

    static void freeData();
private:
    static void buildTileAtlas();
    static void loadTileData();
    static void loadLevels();
};