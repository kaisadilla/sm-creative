#include "assets/Assets.h"
#include "Tile.h"
#include "utils/files.h"

void Assets::loadData () {
    registry = Registry("res/data/registry.json");

    buildTileAtlas();

    int k = 3;
}

void Assets::buildTileAtlas () {
    std::cout << "=== BUILDING TILE ATLAS ===" << std::endl;

    std::vector<sf::Image> tiles;
    i32 tileCount = 0;

    for (const string& imgName : registry.tileSprites) {
        sf::Image image;
        image.loadFromFile("res/sprites/tiles/" + imgName + ".png");

        const i32 sheetWidth = image.getSize().x / registry.tileSize;
        const i32 sheetHeight = image.getSize().y / registry.tileSize;

        tileCount += sheetWidth * sheetHeight;
        tiles.push_back(image);
    }

    i32 atlasRows = 24;
    i32& cellWidth = registry.tileSize;
    i32 atlasWidth = atlasRows * cellWidth;

    sf::Image atlas;
    atlas.create(atlasWidth, atlasWidth, sf::Color(0, 0, 0, 0));

    i32 atlasIndex = 0;

    for (i32 i = 0; i < tiles.size(); i++) {
        sf::Image& tile = tiles[i];

        // for each frame in the spritesheet.
        for (i32 xFrame = 0; xFrame < tile.getSize().x; xFrame += cellWidth) {
            for (i32 yFrame = 0; yFrame < tile.getSize().y; yFrame += cellWidth) {
                ui32 rowPos = atlasIndex / atlasRows;
                ui32 colPos = i - (rowPos * atlasRows);

                ui32 xStartInAtlas = colPos * cellWidth;
                ui32 yStartInAtlas = rowPos * cellWidth;

                ui32 xStartInTile = xFrame;
                ui32 yStartInTile = yFrame;

                // for each pixel in the current frame.
                // TODO: NOT WORKING AS EXPECTED
                for (i32 y = 0; y < cellWidth; y++) {
                    ui32 yAtlas = yStartInAtlas + y;
                    for (i32 x = 0; x < cellWidth; x++) {
                        ui32 xAtlas = xStartInAtlas + x;
                        atlas.setPixel(xAtlas, yAtlas, tile.getPixel(xStartInTile + x, yStartInTile + y));
                    }
                }

                const string tileName = registry.tileSprites[i] + ":" + std::to_string(i);

                tileIndices[tileName] = atlasIndex;
                atlasIndex++;
            }
        }
    }

    atlas.saveToFile("res/sprites/tile_atlas_v2.png");

    texturesPerRow = atlasRows;
    normalizedTextureSize = 1.f / (float)texturesPerRow;

    tileAtlas.loadFromImage(atlas);

    std::cout << "Tile atlas created!" << std::endl;
}

void Assets::loadTileData () {
    std::cout << "=== LOADING TILES ===" << std::endl;

    string str_tiles = utils::readTextFile("res/data/tiles.json");
    json json_tiles = json::parse(str_tiles);

    tiles.push_back(*Tile::airTile(string("air")));

    for (json json_tile : json_tiles) {
        string internalName = json_tile["internalName"];
        string sprite = json_tile["sprite"];
        bool collisionUp = json_tile["collisions"]["up"];
        bool collisionDown = json_tile["collisions"]["down"];
        bool collisionLeft = json_tile["collisions"]["left"];
        bool collisionRight = json_tile["collisions"]["right"];

        i32 tileIndex = tileMap[sprite];
        __tilePositionMap[internalName] = tiles.size();

        Tile tile(internalName, tileAtlas, tileMap[sprite]);
        tile.collisionUp = collisionUp;
        tile.collisionDown = collisionDown;
        tile.collisionLeft = collisionLeft;
        tile.collisionRight = collisionRight;

        tiles.push_back(tile);

        std::cout << "Tile loaded: {" << internalName << "}" << "\n";
    }
}

void Assets::loadLevels () {
    std::cout << "=== LOADING LEVELS ===" << std::endl;

    fs::path folderPath = "res/data/levels";
    fs::directory_iterator folderIterator(folderPath);

    ui32 folderCursor = 0;

    for (fs::directory_entry levelPath : folderIterator) {
        string internalName = levelPath.path().stem().string();

        //data::__remove_Level* level = data::__remove_Level::loadFromFile(levelPath.path().string().c_str());
        //levels[internalName] = *level;

        std::cout << "Level loaded: {" << internalName << "}" << "\n";
        folderCursor++;
    }
}

void Assets::freeData () {
    // TODO: Free certain data such as Levels.
}

void Assets::loadSounds () {
    std::cout << "=== LOADING SOUNDS ===" << std::endl;

    sound_pause.loadFromFile("res/sound/pause.wav");
    sound_jump.loadFromFile("res/sound/jump.wav");
    sound_stomp.loadFromFile("res/sound/stomp.wav");
    sound_kick.loadFromFile("res/sound/kick.wav");
    sound_playerDeath.loadFromFile("res/sound/player_death.wav");
}

void Assets::__test_load_binary () {
    std::ifstream input ("res/level1-1c.sm-binl");
    std::vector<byte_f> buffer(std::istreambuf_iterator<char>(input), {});
    Buffer reader(buffer);

    byte fileType = reader.readUInt8();
    ui16 levelWidth = reader.readUInt16_LE();
    ui16 levelHeight = reader.readUInt16_LE();

    int k = 3;
}