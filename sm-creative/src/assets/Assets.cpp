#include "assets/Assets.h"
#include "utils/files.h"

void Assets::loadData () {
    registry = Registry("res/data/registry.json");

    buildTileAtlas();
    loadSounds();
}

void Assets::freeData () {
    // TODO: Free certain data such as Levels.
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
    tileSize = registry.tileSize;
    i32 atlasWidth = atlasRows * tileSize;

    sf::Image atlas;
    atlas.create(atlasWidth, atlasWidth, sf::Color(0, 0, 0, 0));

    i32 atlasIndex = 0;

    tileIndices.resize(tiles.size());

    for (i32 i = 0; i < tiles.size(); i++) {
        sf::Image& tile = tiles[i];

        int frame = 0;

        // for each frame in the spritesheet.
        for (i32 xFrame = 0; xFrame < tile.getSize().x; xFrame += tileSize) {
            for (i32 yFrame = 0; yFrame < tile.getSize().y; yFrame += tileSize) {
                ui32 rowPos = atlasIndex / atlasRows;
                ui32 colPos = atlasIndex - (rowPos * atlasRows);

                ui32 xStartInAtlas = colPos * tileSize;
                ui32 yStartInAtlas = rowPos * tileSize;

                ui32 xStartInTile = xFrame;
                ui32 yStartInTile = yFrame;

                // for each pixel in the current frame.
                // TODO: NOT WORKING AS EXPECTED
                for (i32 y = 0; y < tileSize; y++) {
                    ui32 yAtlas = yStartInAtlas + y;
                    for (i32 x = 0; x < tileSize; x++) {
                        ui32 xAtlas = xStartInAtlas + x;
                        atlas.setPixel(xAtlas, yAtlas, tile.getPixel(xStartInTile + x, yStartInTile + y));
                    }
                }
                //const ivec2 tileKey = ivec2(i, frame);

                //tileIndices[tileKey] = atlasIndex;
                //tileIndices[i][frame] = atlasIndex;
                tileIndices[i].push_back(atlasIndex);
                atlasIndex++;
                frame++;
            }
        }
    }

    atlas.saveToFile("res/sprites/tile_atlas_v2.png");

    texturesPerRow = atlasRows;
    normalizedTextureSize = 1.f / (float)texturesPerRow;

    tileAtlas.loadFromImage(atlas);

    std::cout << "Tile atlas created!" << std::endl;
}

void Assets::loadSounds () {
    std::cout << "=== LOADING SOUNDS ===" << std::endl;

    sound_pause.loadFromFile("res/sound/pause.wav");
    sound_jump.loadFromFile("res/sound/jump.wav");
    sound_stomp.loadFromFile("res/sound/stomp.wav");
    sound_kick.loadFromFile("res/sound/kick.wav");
    sound_playerDeath.loadFromFile("res/sound/player_death.wav");
    sound_coin.loadFromFile("res/sound/coin.wav");
}

void Assets::loadLevels () {
    std::cout << "=== LOADING LEVELS ===" << std::endl;

}

/***********
 * REMOVE *
***********/

//void Assets::loadLevels () {
//    std::cout << "=== LOADING LEVELS ===" << std::endl;
//
//    fs::path folderPath = "res/data/levels";
//    fs::directory_iterator folderIterator(folderPath);
//
//    ui32 folderCursor = 0;
//
//    for (fs::directory_entry levelPath : folderIterator) {
//        string internalName = levelPath.path().stem().string();
//
//        //data::__remove_Level* level = data::__remove_Level::loadFromFile(levelPath.path().string().c_str());
//        //levels[internalName] = *level;
//
//        std::cout << "Level loaded: {" << internalName << "}" << "\n";
//        folderCursor++;
//    }
//}