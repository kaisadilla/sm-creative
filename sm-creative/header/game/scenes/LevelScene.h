#pragma once

#include "game/scenes/Scene.h"
#include "assets/Assets.h"
#include "tiles/Tile.h"
#include "entities/Entity.h"
#include "player/Camera.h"

class LevelScene : public Scene {
    friend class LevelReader;

private:
    ui32 width = 0;
    ui32 height = 0;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundImage;
    sf::Music music;

    std::vector<std::unique_ptr<Tile>> backgroundLayer;
    std::vector<std::unique_ptr<Tile>> foregroundLayer;
    std::vector<std::unique_ptr<Tile>> detailLayer;
    std::vector<std::unique_ptr<Tile>> frontLayer;

    std::vector<std::unique_ptr<Entity>> entities;

    Camera camera;

public:
    LevelScene();

    void onEnter() override;
    void onDraw(sf::RenderWindow& window) override;

private:
    void loadBackground(const string& name);
    void loadMusic(const string& name);

    void drawLayer(sf::RenderWindow& window, std::vector<std::unique_ptr<Tile>>& layer);

public:
    inline ui32 getWidth () const {
        return width;
    }

    inline ui32 getHeight () const {
        return height;
    }
};