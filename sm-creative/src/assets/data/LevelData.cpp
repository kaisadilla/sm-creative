#include <fstream>

#include "assets/data/LevelData.h"
#include "libraries/Buffer.hpp"

LevelData* LevelData::fromBinaryFile (const string& path) {
    std::ifstream input("res/level1-1.sm-binl");
    std::vector<byte_f> buffer(std::istreambuf_iterator<char>(input), {});
    Buffer reader(buffer);

    LevelData* level = new LevelData();

    const ui32 fileType = reader.readUInt8();
    const ui32 versionMajor = reader.readUInt8();
    const ui32 versionMinor = reader.readUInt8();
    const ui32 versionRevision = reader.readUInt8();

    const ui32 width = reader.readUInt16_LE();
    const ui32 height = reader.readUInt16_LE();

    const ui32 background = reader.readUInt16_LE();
    const ui32 music = reader.readUInt16_LE();

    //std::ifstream input ("res/level1-1c.sm-binl");
    //std::vector<byte_f> buffer(std::istreambuf_iterator<char>(input), {});
    //Buffer reader(buffer);
    //
    //byte fileType = reader.readUInt8();
    //ui16 levelWidth = reader.readUInt16_LE();
    //ui16 levelHeight = reader.readUInt16_LE();
    //
    //int k = 3;

    return nullptr;
}
