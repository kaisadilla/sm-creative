#include "game/scenes/LevelReader.h"
#include "tiles/TileReader.h"
#include "entities/EntityReader.h"
#include "utils/files.h"

LevelScene* LevelReader::loadLevel(const string& fileName) {
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

    readLayer(reader, level->backgroundLayer, false);
    readLayer(reader, level->foregroundLayer, true);
    readLayer(reader, level->detailLayer, false);
    readLayer(reader, level->frontLayer, false);

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

    return level;
}

void LevelReader::readLayer (Buffer& reader, std::vector<std::unique_ptr<Tile>>& tiles, const bool generateColliders) {
    const ui32 tileCount = reader.readUInt32_LE();
    tiles.resize(tileCount);

    for (i32 i = 0; i < tileCount; i++) {
        Tile* tile = TileReader::getNextTile(reader, generateColliders);
        tiles[i] = std::unique_ptr<Tile>(tile);
    }
}
