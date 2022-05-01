#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "BitmapFont.h"

class BitmapText : public sf::Drawable {
public:
    enum class TextAlign {
        Left = 0,
        Right = 1
    };

private:
    BitmapFont font;
    TextAlign align = TextAlign::Left;
    vec2 scale = vec2(1, 1);
    vec2 pivot = vec2(0, 0);
    std::vector<sf::Sprite> stringSprites;

public:
    BitmapText() {};

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setString(const string& string);

public:
    inline void setAlign (const TextAlign align) {
        this->align = align;
    }

    inline void setPivot (const vec2& position) {
        this->pivot = position;
    }

    inline void setPivot (const f32 x, const f32 y) {
        this->pivot = vec2(x, y);
    }

    inline void setFont (const BitmapFont& font) {
        this->font = font;
    }

    inline void setScale (const vec2 scale) {
        this->scale = scale;
    }

    inline void setScale (const f32 scale) {
        this->scale = vec2(scale, scale);
    }
};