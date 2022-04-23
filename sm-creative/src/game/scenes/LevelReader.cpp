#include "game/scenes/LevelReader.h"
#include "libraries/Buffer.hpp"
#include "tiles/TileReader.h"
#include "entities/EntityReader.h"

LevelScene* LevelReader::loadLevel(const string& fileName) {
    std::ifstream input("res/data/levels/" + fileName + ".sm-binl");
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
    level->backgroundLayer.resize(backgroundTileCount);
    for (i32 i = 0; i < backgroundTileCount; i++) {
        Tile* tile = TileReader::getNextTile(reader);
        level->backgroundLayer[i] = std::unique_ptr<Tile>(tile);
    }

    const ui32 foregroundTileCount = reader.readUInt32_LE();
    level->foregroundLayer.resize(foregroundTileCount);
    for (i32 i = 0; i < foregroundTileCount; i++) {
        Tile* tile = TileReader::getNextTile(reader);
        level->foregroundLayer[i] = std::unique_ptr<Tile>(tile);
    }

    const ui32 detailTileCount = reader.readUInt32_LE();
    level->detailLayer.resize(detailTileCount);
    for (i32 i = 0; i < detailTileCount; i++) {
        Tile* tile = TileReader::getNextTile(reader);
        level->detailLayer[i] = std::unique_ptr<Tile>(tile);
    }

    const ui32 frontTileCount = reader.readUInt32_LE();
    level->frontLayer.resize(frontTileCount);
    for (i32 i = 0; i < frontTileCount; i++) {
        Tile* tile = TileReader::getNextTile(reader);
        level->frontLayer[i] = std::unique_ptr<Tile>(tile);
    }

    const ui32 entityCount = reader.readUInt16_LE();
    level->entities.resize(entityCount);
    for (i32 i = 0; i < entityCount; i++) {
        Entity* entity = EntityReader::getNextEntity(reader);
        level->entities[i] = std::unique_ptr<Entity>(entity);
    }

    int k = 3;

    return level;
}
