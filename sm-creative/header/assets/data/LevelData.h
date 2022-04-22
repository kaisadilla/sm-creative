#pragma once

#include "root.h"

class LevelData {
private:
    i32 versionMajor;
    i32 versionMinor;
    i32 versionRevision;

    i32 width;
    i32 height;

    i32 background;
    i32 music;

public:
    LevelData() {};

    static LevelData* fromBinaryFile (const string& path);
};