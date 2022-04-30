#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "root.h"
#include "nlohmann/json.hpp"

class BitmapFont {
    typedef nlohmann::json json;

private:
    sf::Texture texture;
    std::unordered_map<byte, sf::IntRect> characters;
    vec2 spacing;

public:
    BitmapFont() {};

    void loadFromFile (const string& filePath);

public:
    inline const sf::Texture& getTexture () {
        return texture;
    }

    inline const sf::IntRect getCharacterRect (const byte character) {
        return characters[character];
    }
};