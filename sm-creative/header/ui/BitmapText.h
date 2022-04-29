#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "BitmapFont.h"

class BitmapText : public sf::Drawable {
private:
    BitmapFont font;
    vec2 position = vec2(0, 0);
    std::vector<sf::Sprite> stringSprites;

public:
    BitmapText() {};

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(const vec2& position);
    void setFont(const BitmapFont& font);
    void setString(const string& string);
};