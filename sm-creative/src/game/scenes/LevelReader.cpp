#include "game/scenes/LevelReader.h"
#include "tiles/TileReader.h"
#include "entities/EntityReader.h"
#include "utils/files.h"

#include <chrono>

LevelScene* LevelReader::loadLevel(const string& fileName) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    //std::ifstream input("res/data/levels/" + fileName + ".sm-binl", std::ios::in | std::ios::binary);
    //std::vector<byte_f> buffer((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    auto& buffer = utils::readBinaryFile("res/data/levels/" + fileName + ".sm-binl");
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
    const ui32 time = reader.readUInt16_LE();

    readLayer(reader, level, level->backgroundLayer, false);
    readLayer(reader, level, level->foregroundLayer, true);
    readLayer(reader, level, level->detailLayer, false);
    readLayer(reader, level, level->frontLayer, false);

    const ui32 entityCount = reader.readUInt16_LE();
    level->entities.resize(entityCount);
    for (i32 i = 0; i < entityCount; i++) {
        Entity* entity = EntityReader::getNextEntity(reader);
        entity->setLevel(level);
        level->entities[i] = std::unique_ptr<Entity>(entity);
    }

    level->width = width;
    level->height = height;

    level->loadBackground(Assets::getBackgroundImageAt(background));
    level->loadMusic(Assets::getMusicAt(music));

    level->timeLeft = (f32)time;

    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << "Loaded level in " << ms_int.count() << "ms.\n";

    return level;
}

void LevelReader::readLayer (Buffer& reader, LevelScene* level, std::vector<std::unique_ptr<Tile>>& tiles, const bool generateColliders) {
    const ui32 tileCount = reader.readUInt32_LE();
    tiles.resize(tileCount);

    for (i32 i = 0; i < tileCount; i++) {
        Tile* tile = TileReader::getNextTile(reader, generateColliders);
        tile->setLevel(level);
        tiles[i] = std::unique_ptr<Tile>(tile);
    }
}
