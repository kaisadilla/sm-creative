#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "Debug.h"
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

    Grid2<WorldTile> foregroundLayer;
    std::vector<Collider> colliders;

    Camera camera;

    sf::Texture __texBackground;
    sf::Sprite __background;

    Player player;

    std::vector<Enemy*> enemies;

public:
    SceneLevel();
    SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const Level& level);
    ~SceneLevel();

    void onEnter();
    void onUpdate(const f32 deltaTime);
    void onFixedUpdate(const f32 fixedTime);
    void onDraw(sf::RenderWindow& window);
    void onLateUpdate();

private:
    void drawLevel(sf::RenderWindow& window);
    void drawMobs(sf::RenderWindow& window);
    void drawPlayer(sf::RenderWindow& window);
    void drawColliders(sf::RenderWindow& window);

public:
    i32 getWidth () {
        return levelTileWidth * PIXELS_PER_TILE;
    }

    i32 getHeight () {
        return levelTileHeight * PIXELS_PER_TILE;
    }
};