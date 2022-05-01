#pragma once

#include "Debug.h"
#include "game/scenes/Scene.h"
#include "assets/Assets.h"
#include "tiles/Tile.h"
#include "entities/Entity.h"
#include "entities/Player.h"
#include "player/Camera.h"
#include "game/UserInterface.h"
#include "vfx/Particle.h"

class LevelScene : public Scene {
    friend class LevelReader;

private:
    ui32 width = 0;
    ui32 height = 0;

    /************************
     * BACKGROUND AND MUSIC *
     ************************/
    f32 backgroundParallaxMaxX = 0;
    f32 backgroundParallaxMaxY = 0;
    f32 levelParallaxMaxX = 0;
    f32 levelParallaxMaxY = 0;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundImage;
    sf::Music music;

    std::vector<std::unique_ptr<Tile>> backgroundLayer;
    std::vector<std::unique_ptr<Tile>> foregroundLayer;
    std::vector<std::unique_ptr<Tile>> detailLayer;
    std::vector<std::unique_ptr<Tile>> frontLayer;

    std::vector<std::unique_ptr<Entity>> entities;

    std::vector<std::unique_ptr<Particle>> particles;

    Player player;
    Camera camera;

    bool isLevelPaused = false;

    /**********
     * SCORES *
     **********/
    f32 timeLeft = 999;

    UserInterface ui;

    // TODO: Temporary fields that will be replaced when this is properly implemented.
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

    i32 addLives(const i32 lives);
    i32 addCoins(const i32 coins);
    i32 addScore(const i32 score);

    // TODO: Someday, this will be pooled.
    /// <summary>
    /// Adds a particle to the level. This method will call the onStart() event on the
    /// particle, so it doesn't need to be called before.
    /// </summary>
    /// <param name="particle">The particle to instantiate inside the level.</param>
    void instantiateParticle(std::unique_ptr<Particle>& particle);

private:
    void loadBackground(const string& name);
    void loadMusic(const string& name);

    void drawLayer(sf::RenderWindow& window, std::vector<std::unique_ptr<Tile>>& layer);
    void drawEntities(sf::RenderWindow& window);
    void drawPlayer(sf::RenderWindow& window);
    void drawParticles(sf::RenderWindow& window);
    void drawColliders(sf::RenderWindow& window);
    void drawDebugInfo(sf::RenderWindow& window);

    void deleteDisposedObjects();

    void initializeBackground();
    void updateBackgroundPosition();

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