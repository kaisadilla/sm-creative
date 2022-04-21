#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>

#include "root.h"
#include "assets/Registry.h"
#include "libraries/Buffer.hpp"

namespace fs = std::filesystem;

class Tile;
namespace data {
    class Level;
}

class Assets {
    typedef nlohmann::json json;

public:
    /// <summary>
    /// Stores the position of each tile sprite inside the array. For spritesheets,
    /// every frame will be stored at its own index using the suffix ":n", where n
    /// is the position of the frame in the spritesheet.
    /// </summary>
    inline static std::unordered_map<string, i32> tileIndices;
    inline static sf::Texture tileAtlas;


    inline static std::vector<Tile> tiles;
    inline static i32 texturesPerRow;
    inline static f32 normalizedTextureSize;
    inline static std::unordered_map<string, i32> __tilePositionMap;

    inline static sf::SoundBuffer sound_pause;
    inline static sf::SoundBuffer sound_jump;
    inline static sf::SoundBuffer sound_stomp;
    inline static sf::SoundBuffer sound_kick;
    inline static sf::SoundBuffer sound_playerDeath;

private:
    inline static Registry registry;

    inline static std::unordered_map<string, i32> tileMap;

public:
    static void loadData();

    static void __loadData () {
        __test_load_binary();

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
    static void __test_load_binary();
};