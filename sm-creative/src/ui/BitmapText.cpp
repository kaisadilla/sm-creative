#include "ui/BitmapText.h"

void BitmapText::draw (sf::RenderTarget& target, sf::RenderStates states) const {
    for (const sf::Sprite& sprite : stringSprites) {
        target.draw(sprite, states);
    }
}

void BitmapText::setString (const string& string) {
    stringSprites.clear();

    int xOffset = 0;

    for (byte c : string) {
        c = ::toupper(c);
        sf::IntRect rect = font.getCharacterRect(c);

        sf::Sprite charSprite;
        charSprite.setScale(scale);
        charSprite.setTexture(font.getTexture());
        charSprite.setTextureRect(rect);
        charSprite.setPosition(position.x + xOffset, position.y);

        xOffset += rect.width * scale.x;
        stringSprites.push_back(charSprite);
    }
}
