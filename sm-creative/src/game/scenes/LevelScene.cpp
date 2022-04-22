#include <fstream>

#include "game/scenes/LevelScene.h"
#include "libraries/Buffer.hpp"
#include "tiles/TileReader.h"

LevelScene::LevelScene () {}

LevelScene::LevelScene (const string& path) {
    std::ifstream input("res/level1-1.sm-binl");
    std::vector<byte_f> buffer(std::istreambuf_iterator<char>(input), {});
    Buffer reader(buffer);

    LevelScene* level = new LevelScene();

    const ui32 fileType = reader.readUInt8();
    const ui32 versionMajor = reader.readUInt8();
    const ui32 versionMinor = reader.readUInt8();
    const ui32 versionRevision = reader.readUInt8();

    const ui32 width = reader.readUInt16_LE();
    const ui32 height = reader.readUInt16_LE();

    const ui32 background = reader.readUInt16_LE();
    const ui32 music = reader.readUInt16_LE();

    // background layer
    const ui32 backgroundTileCount = reader.readUInt32_LE();
    //level->backgroundLayer = std::vector<std::unique_ptr<Tile>>(backgroundTileCount);
    for (i32 i = 0; i < backgroundTileCount; i++) {
        //Tile* tile = TileReader::getNextTile(reader);
        //level->backgroundLayer[i] = std::unique_ptr<Tile>(tile);
    }
}
