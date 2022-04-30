#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"

class Game;

class Scene {
protected:
    uvec2 windowSize;
    vec2 windowZoom;
    Game* game;

public:
    virtual void setWindowSize(const uvec2& size, const vec2& zoom);

    virtual void onEnter() = 0;
    virtual void onUpdate() = 0;
    virtual void onFixedUpdate() = 0;
    virtual void onLateUpdate() = 0;
    virtual void onDraw(sf::RenderWindow& window) = 0;
    virtual void onEvent(const sf::Event& evt) = 0;

public:
    inline void setGame (Game* game) {
        this->game = game;
    }
};