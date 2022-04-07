#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "player/Camera.h"
#include "world/Level.h"
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

    sf::Texture __texPlayer;
    Player player;

public:
    SceneLevel();
    SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const Level& level);

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
};