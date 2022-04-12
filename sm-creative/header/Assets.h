#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>

#include "root.h"

namespace fs = std::filesystem;

class Tile;
namespace data {
    class Level;
}

class Assets {
    typedef nlohmann::json json;

public:
    inline static sf::Texture tilesAtlas;
    inline static std::vector<Tile> tiles;
    inline static i32 texturesPerRow;
    inline static f32 normalizedTextureSize;
    inline static std::unordered_map<string, i32> __tilePositionMap;
    inline static std::unordered_map<string, data::Level> levels;

    inline static sf::SoundBuffer sound_pause;
    inline static sf::SoundBuffer sound_jump;
    inline static sf::SoundBuffer sound_stomp;
    inline static sf::SoundBuffer sound_kick;
    inline static sf::SoundBuffer sound_playerDeath;

private:
    inline static std::unordered_map<string, i32> tileMap;

public:
    static void loadData () {
        tiles = std::vector<Tile>();
        buildTileAtlas();
        loadTileData();
        loadSounds();
        loadLevels();
    }

    static void freeData();
private:
    static void buildTileAtlas();
    static void loadTileData();
    static void loadSounds();
    static void loadLevels();
};