#pragma once

#include "root.h"

class LevelData {
private:
    i32 versionMajor;
    i32 versionMinor;
    i32 versionRevision;

    i32 width;
    i32 height;

public:
    LevelData() {};

    static LevelData* fromBinaryFile (const string& path);
};