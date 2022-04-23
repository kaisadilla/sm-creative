#pragma once

#include "game/scenes/Scene.h"
#include "assets/Assets.h"
#include "tiles/Tile.h"
#include "entities/Entity.h"

class LevelScene : public Scene {
    friend class LevelReader;

private:
    i32 width = 0;
    i32 height = 0;

    sf::Texture texBackground;
    sf::Sprite background;
    sf::Music music;

    std::vector<std::unique_ptr<Tile>> backgroundLayer;
    std::vector<std::unique_ptr<Tile>> foregroundLayer;
    std::vector<std::unique_ptr<Tile>> detailLayer;
    std::vector<std::unique_ptr<Tile>> frontLayer;

    std::vector<std::unique_ptr<Entity>> entities;

public:
    LevelScene();

private:

};