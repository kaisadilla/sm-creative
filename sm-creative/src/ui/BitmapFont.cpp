#include <utils/files.h>

#include "ui/BitmapFont.h"

void BitmapFont::loadFromFile (const string& filePath) {
    string str_font = utils::readTextFile(filePath.c_str());
    json json_font = json::parse(str_font);

    const string spritesheet = json_font["spritesheet"];
    const ivec2 sheetDims(json_font["spritesheetDimensions"][0], json_font["spritesheetDimensions"][1]);
    const ivec2 cellDims(json_font["cellDimensions"][0], json_font["cellDimensions"][1]);
    const sf::IntRect cellOffset(json_font["cellOffset"][0], json_font["cellOffset"][1], json_font["cellOffset"][2], json_font["cellOffset"][3]);
    const i32 spaceLength = json_font["spaceLength"];

    characters[' '] = sf::IntRect(0, 0, spaceLength, 0);

    for (const auto& character : json_font["characters"]) {
        const byte ascii = ((string)character["character"])[0];
        const i32 index = character["index"];

        sf::IntRect charOffset;
        if (character.contains("offset")) {
            charOffset = sf::IntRect(character["offset"][0], character["offset"][1], character["offset"][2], character["offset"][3]);
        }
        else {
            charOffset = cellOffset;
        }

        const i32 row = index / sheetDims.x;
        const i32 col = index % sheetDims.x;

        const i32 left = (col * cellDims.x) + charOffset.left;
        const i32 top = (row * cellDims.y) + charOffset.top;
        const i32 width = cellDims.x - charOffset.left - charOffset.width;
        const i32 height = cellDims.y - charOffset.top - charOffset.height;

        characters[ascii] = sf::IntRect(left, top, width, height);
    }

    spacing = vec2(json_font["spacing"][0], json_font["spacing"][1]);

    texture.loadFromFile("res/sprites/bitfonts/" + spritesheet + ".png");
}