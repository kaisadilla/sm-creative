#pragma once

#include "root.h"
#include "LevelScene.h"
#include "libraries/Buffer.hpp"

class LevelReader {
public:
    static LevelScene* loadLevel(const string& fileName);

private:
    static void readLayer(Buffer& reader, LevelScene* level, std::vector<std::unique_ptr<Tile>>& tiles, const bool generateColliders);
};