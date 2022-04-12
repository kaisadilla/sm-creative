#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "Debug.h"
#include "SM_Time.h"
#include "player/Camera.h"
#include "data/Level.h"
#include "characters/Entity.h"
#include "characters/Mob.h"
#include "characters/Player.h"

class SceneLevel {
private:
    ui32 windowWidth;
    ui32 windowHeight;

    ui32 levelTileWidth;
    ui32 levelTileHeight;

    Grid2<WorldTile> backgroundLayer;
    Grid2<WorldTile> foregroundLayer;
    std::vector<Collider> colliders;

    Camera camera;

    sf::Texture __texBackground;
    sf::Sprite __background;
    sf::Music levelMusic;

    Player player;

    std::vector<Mob*> enemies;
    //std::vector<std::unique_ptr<Enemy>> enemies;
    //std::map<i32, std::unique_ptr<Enemy>> enemies;

    i32 nextId = 0;

    bool isLevelPaused = false;

    sf::Texture texPause;
    sf::Sprite spritePause;
    sf::Sound sound_pause;

public:
    SceneLevel();
    SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const data::Level& level);
    ~SceneLevel();

    void onEnter();
    void onUpdate();
    void onFixedUpdate();
    void onDraw(sf::RenderWindow& window);
    void onLateUpdate();
    void onEvent(const sf::Event& evt);

    void deleteDisposedEnemies();

private:
    void drawLevel(sf::RenderWindow& window);
    void drawLayer(sf::RenderWindow& window, Grid2<WorldTile>& layer);
    void drawMobs(sf::RenderWindow& window);
    void drawPlayer(sf::RenderWindow& window);
    void drawColliders(sf::RenderWindow& window);
    void drawDebugInfo(sf::RenderWindow& window);

public:
    inline i32 getWidth () const {
        return levelTileWidth * PIXELS_PER_TILE;
    }

    inline i32 getHeight () const {
        return levelTileHeight * PIXELS_PER_TILE;
    }

    inline i32 getNextId () {
        return nextId++;
    }

    /// <summary>
    /// Returns a pointer to the tile in the foreground layer at that position, if it exists.
    /// If the position lays outside of the level, it returns a null pointer.
    /// </summary>
    /// <param name="x">The x coordinate in the tile grid.</param>
    /// <param name="y">The y coordinate in the tile grid.</param>
    /// <returns></returns>
    inline WorldTile* getTileAt (const i32 x, const i32 y) {
        if (x < 0 || x >= foregroundLayer.getWidth() || y < 0 || y >= foregroundLayer.getHeight()) {
            return nullptr;
        }
        else {
            return &foregroundLayer.getAt(x, y);
        }
    }
};