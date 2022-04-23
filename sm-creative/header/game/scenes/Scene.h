#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"

class Scene {
protected:
    uvec2 windowSize;
    vec2 windowZoom;

public:
    virtual void setWindowSize(const uvec2& size, const vec2& zoom);

    virtual void onEnter() = 0;
    virtual void onDraw(sf::RenderWindow& window) = 0;
};