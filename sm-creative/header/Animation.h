#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"

class Animation {
public:
    sf::IntRect uvRect;

private:
    uvec2 imageCount;
    uvec2 currentImage;

    f32 totalTime;
    f32 switchTime;

public:
    Animation(sf::Texture* pointer, uvec2 imageCount, f32 switchTime);
    ~Animation();
};