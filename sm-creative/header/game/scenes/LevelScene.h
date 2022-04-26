#pragma once

#include "Debug.h"
#include "game/scenes/Scene.h"
#include "assets/Assets.h"
#include "tiles/Tile.h"
#include "entities/Entity.h"
#include "entities/Player.h"
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

    Player player;
    Camera camera;

    bool isLevelPaused = false;

    // TODO: Temporary
    sf::Texture __TEMPORARY_texPause;
    sf::Sprite __TEMPORARY_spritePause;
    sf::Sound __TEMPORARY_sound_pause;

public:
    LevelScene();
    ~LevelScene();

    void onEnter() override;
    void onUpdate() override;
    void onFixedUpdate() override;
    void onLateUpdate() override;
    void onDraw(sf::RenderWindow& window) override;
    void onEvent(const sf::Event& evt) override;

private:
    void loadBackground(const string& name);
    void loadMusic(const string& name);

    void drawLayer(sf::RenderWindow& window, std::vector<std::unique_ptr<Tile>>& layer);
    void drawEntities(sf::RenderWindow& window);
    void drawPlayer(sf::RenderWindow& window);
    void drawColliders(sf::RenderWindow& window);
    void drawDebugInfo(sf::RenderWindow& window);

    void deleteDisposedEntities();

public:
    inline ui32 getGridWidth () const {
        return width;
    }

    inline ui32 getGridHeight () const {
        return height;
    }

    inline ui32 getPixelWidth () const {
        return width * PIXELS_PER_TILE;
    }

    inline ui32 getPixelHeight () const {
        return height * PIXELS_PER_TILE;
    }

private:
    void __TEMPORARY_initialize_player();
};