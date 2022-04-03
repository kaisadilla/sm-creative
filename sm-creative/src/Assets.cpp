#include "Assets.h"

void Assets::buildTileAtlas () {
    std::cout << "=== BUILDING TILE ATLAS ===" << std::endl;

    fs::path folderPath = "res/sprites/tiles";
    fs::directory_iterator folderIterator(folderPath);

    std::vector<sf::Image> tiles;

    ui32 maxWidth = 0;
    ui32 folderCursor = 0;

    for (fs::directory_entry imgPath : folderIterator) {
        string internalName = imgPath.path().stem().string();
        tileMap[internalName] = folderCursor;

        sf::Image img;
        img.loadFromFile(imgPath.path().string());

        maxWidth = std::max({maxWidth, img.getSize().x, img.getSize().y});

        tiles.push_back(img);

        std::cout << "Tile loaded: {" << internalName << "}" << "\n";
        folderCursor++;
    }

    i32 atlasRows = 24; // todo: calculate this
    i32 cellWidth = maxWidth; // todo: calculate this with maxWidth
    i32 atlasWidth = atlasRows * cellWidth;

    sf::Image atlas;
    atlas.create(atlasWidth, atlasWidth, sf::Color(0, 0, 0, 0));

    for (ui32 i = 0; i < tiles.size(); i++) {
        sf::Image& tile = tiles[i];

        ui32 rowPos = i / atlasRows;
        ui32 colPos = i - (rowPos * atlasRows);

        ui32 xStart = colPos * cellWidth;
        ui32 yStart = rowPos * cellWidth;

        for (ui32 y = 0; y < tile.getSize().y; y++) {
            ui32 yAtlas = yStart + y;
            ui32 yTile = y / (tile.getSize().y / (f32)cellWidth);

            for (ui32 x = 0; x < tile.getSize().x; x++) {
                ui32 xAtlas = xStart + x;
                ui32 xTile = x / (tile.getSize().x / (f32)cellWidth);

                atlas.setPixel(xAtlas, yAtlas, tile.getPixel(xTile, yTile));
            }
        }
    }

    atlas.saveToFile("res/sprites/tile_atlas.png");

    texturesPerRow = atlasRows;
    normalizedTextureSize = 1.f / (float)texturesPerRow;

    tilesAtlas.loadFromImage(atlas);

    std::cout << "Tile atlas created!" << std::endl;
}

void Assets::loadTileData () {
    string str_tiles = utils::readTextFile("res/data/tiles.json");
    json json_tiles = json::parse(str_tiles);

    tiles.push_back(*Tile::airTile(string("air")));

    for (json json_tile : json_tiles) {
        string internalName = json_tile["internalName"];
        string sprite = json_tile["sprite"];

        i32 tile = tileMap[sprite];

        __tilePositionMap[internalName] = tiles.size();
        tiles.push_back(Tile(internalName, tilesAtlas, tileMap[sprite]));
    }
}

void Assets::loadLevels () {
    std::cout << "=== LOADING LEVELS ===" << std::endl;

    fs::path folderPath = "res/data/levels";
    fs::directory_iterator folderIterator(folderPath);

    ui32 folderCursor = 0;

    for (fs::directory_entry levelPath : folderIterator) {
        string internalName = levelPath.path().stem().string();

        Level* level = Level::loadFromFile(levelPath.path().string().c_str());
        levels[internalName] = *level;

        std::cout << "Level loaded: {" << internalName << "}" << "\n";
        folderCursor++;
    }
}

void Assets::freeData () {
    // TODO: Free certain data such as Levels.
}
