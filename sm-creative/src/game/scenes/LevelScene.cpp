#include <fstream>

#include "game/scenes/LevelScene.h"

LevelScene::LevelScene () {}

void LevelScene::onEnter () {
    camera = Camera(uvec2(width, height), uvec2(windowSize.x / windowZoom.x, windowSize.y / windowZoom.y));
    camera.updatePosition(vec2(5 * 16, 20 * 16));
}

void LevelScene::onDraw (sf::RenderWindow& window) {
    window.draw(backgroundImage);

    window.setView(camera.getView());
    drawLayer(window, backgroundLayer);
    drawLayer(window, foregroundLayer);
    window.setView(window.getDefaultView());
}

void LevelScene::loadBackground (const string& name) {
    backgroundTexture.loadFromFile("res/sprites/backgrounds/" + name + ".png");
    backgroundImage.setTexture(backgroundTexture);
    backgroundImage.setScale(vec2(2.f, 2.f));
}

void LevelScene::loadMusic (const string& name) {
    music.openFromFile("res/music/" + name + ".wav");
    music.setLoop(true);
    music.setVolume(50.f);
}

void LevelScene::drawLayer (sf::RenderWindow& window, std::vector<std::unique_ptr<Tile>>& layer) {
    for (const auto& tile : layer) {
        tile->draw(window);
    }
}