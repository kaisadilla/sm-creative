#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>

#include "root.h"
#include "assets/Registry.h"
#include "assets/data/LevelData.h"

namespace fs = std::filesystem;

class Assets {
    typedef nlohmann::json json;

private:
    inline static Registry registry;

    inline static std::unordered_map<string, i32> tileMap; // remove

public:
    /// <summary>
    /// Stores the position of each tile sprite frame inside the array. The key is a ivec2
    /// containing the index of the tile sprite and the index of the frame. For static sprites,
    /// the index of the frame will always be 0.
    /// </summary>
    inline static std::vector<std::vector<i32>> tileIndices;
    //inline static std::unordered_map<ivec2, i32> tileIndices;
    inline static i32 tileSize;
    inline static i32 texturesPerRow;
    inline static sf::Texture tileAtlas;

    inline static std::unordered_map<string, LevelData> levels;

    inline static f32 normalizedTextureSize; // remove
    inline static std::unordered_map<string, i32> __tilePositionMap; // remove

    inline static sf::SoundBuffer sound_pause;
    inline static sf::SoundBuffer sound_jump;
    inline static sf::SoundBuffer sound_stomp;
    inline static sf::SoundBuffer sound_kick;
    inline static sf::SoundBuffer sound_playerDeath;
    inline static sf::SoundBuffer sound_coin;

public:
    static void loadData();
    static void freeData();

public:
    static inline string getBackgroundImageAt (const i32 index) {
        return registry.backgroundImages[index];
    }

    static inline string getMusicAt (const i32 index) {
        return registry.music[index];
    }
    
    static inline string getEntitySpriteAt (const i32 index) {
        return registry.entitySprites[index];
    }

private:
    static void buildTileAtlas();
    static void loadSounds();
    static void loadLevels();
};