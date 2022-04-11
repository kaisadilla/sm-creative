#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "Debug.h"
#include "SM_Time.h"
#include "player/Camera.h"
#include "world/Level.h"
#include "mobs/Mob.h"
#include "mobs/Enemy.h"
#include "mobs/Goomba.h"
#include "mobs/Player.h"

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

    std::vector<Enemy*> enemies;
    //std::vector<std::unique_ptr<Enemy>> enemies;
    //std::map<i32, std::unique_ptr<Enemy>> enemies;

    i32 ids = 0;

public:
    SceneLevel();
    SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const Level& level);
    ~SceneLevel();

    void onEnter();
    void onUpdate();
    void onFixedUpdate();
    void onDraw(sf::RenderWindow& window);
    void onLateUpdate();

    void deleteDisposedEnemies();

private:
    void drawLevel(sf::RenderWindow& window);
    void drawLayer(sf::RenderWindow& window, Grid2<WorldTile>& layer);
    void drawMobs(sf::RenderWindow& window);
    void drawPlayer(sf::RenderWindow& window);
    void drawColliders(sf::RenderWindow& window);

public:
    inline i32 getWidth () {
        return levelTileWidth * PIXELS_PER_TILE;
    }

    inline i32 getHeight () {
        return levelTileHeight * PIXELS_PER_TILE;
    }

    inline i32 getNextId () {
        return ids++;
    }
};