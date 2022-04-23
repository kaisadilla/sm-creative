#pragma once

#include "root.h"
#include "LevelScene.h"

class LevelReader {
public:
    static LevelScene* loadLevel(const string& fileName);
};