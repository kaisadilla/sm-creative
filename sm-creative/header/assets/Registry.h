#pragma once

#include <nlohmann/json.hpp>
#include "root.h"

class Registry {
    typedef nlohmann::json json;

public:
    inline static std::vector<string> backgroundImages;
    inline static std::vector<string> music;
    inline static i32 tileSize;
    inline static std::vector<string> tileSprites;
    inline static std::vector<string> entitySprites;
    inline static std::vector<string> particleSprites;

public:
    Registry() {}
    Registry(const string& path);
};