#include "game/scenes/SceneLevel.h"

SceneLevel::SceneLevel() :
    windowWidth(0),
    windowHeight(0),
    levelTileWidth(0),
    levelTileHeight(0),
    foregroundLayer(0, 0),
    player(this, vec2(16.f, 16.f))
{}

SceneLevel::SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const Level& level) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    levelTileWidth(level.getLevelWidth()),
    levelTileHeight(level.getLevelHeight()),
    player(this, vec2(16.f, 16.f)),
    foregroundLayer(level.getForegroundPlane())
{
    for (i32 x = 0; x < levelTileWidth; x++) {
        for (i32 y = 0; y < levelTileHeight; y++) {
            WorldTile& worldTile = foregroundLayer.getAt(x, y);
            // TODO: This may be better as part of the world tile. The scenelevel'd only keep a vector
            // of references to worldtiles that have colliders.
            if (!worldTile.getTile()->isAirTile()) {
                colliders.push_back(Collider(&worldTile, vec2(x * 16 + 8, y * 16 + 8), vec2(8, 8)));
            }
        }
    }
}

SceneLevel::~SceneLevel () {
    for (auto enemy : enemies) {
        delete enemy;
    }
}

void SceneLevel::onEnter () {
    camera = Camera(uvec2(foregroundLayer.getWidth() * 16, foregroundLayer.getHeight() * 16), uvec2(windowWidth, windowHeight));

    __texBackground.loadFromFile("res/sprites/backgrounds/default_0.png");
    
    __background.setTexture(__texBackground);
    __background.setScale(vec2(2.f, 2.f));

    player.setSprite("res/sprites/characters/mario.png", uvec2(16, 16));
    player.setPosition(vec2(2.f, 26.f));

    enemies.push_back(new Goomba(this, vec2(16.f, 16.f), true));
    enemies[0]->setSprite("res/sprites/characters/goomba.png", uvec2(16, 16));
    enemies[0]->setPosition(vec2(8.f * 16.f, 25.f * 16.f));
    enemies[0]->onStart();
}

void SceneLevel::onUpdate (const f32 deltaTime) {
    for (auto& enemy : enemies) {
        enemy->onUpdate(deltaTime);
    }

    player.onUpdate(deltaTime);
    camera.updatePosition(player.getPixelPosition());
}

void SceneLevel::onFixedUpdate (const f32 fixedTime) {
    for (auto& enemy : enemies) {
        enemy->onFixedUpdate(fixedTime);
        enemy->checkCollisionsWithTiles(colliders);
    }

    player.onFixedUpdate(fixedTime);
    player.checkCollisionsWithTiles(colliders);
    player.checkCollisionWithEnemies(enemies);
}

void SceneLevel::onDraw (sf::RenderWindow& window) {
    window.draw(__background);

    window.setView(camera.getView());
    drawLevel(window);
    drawMobs(window);
    drawPlayer(window);

    if (Debug::drawCollisions) drawColliders(window);

    window.setView(window.getDefaultView());
}

void SceneLevel::onLateUpdate () {

}

void SceneLevel::drawLevel (sf::RenderWindow& window) {
    // TODO: Check if sf::View culls tiles outside the viewport or not.
    for (i32 x = 0; x < levelTileWidth; x++) {
        f32 xPixel = x * PIXELS_PER_TILE;

        for (i32 y = 0; y < levelTileHeight; y++) {
            f32 yPixel = y * PIXELS_PER_TILE;

            WorldTile worldTile = foregroundLayer.getAt(x, y);
            worldTile.draw(window, vec2(xPixel, yPixel));
        }
    }
}

void SceneLevel::drawMobs (sf::RenderWindow& window) {
    for (const auto& enemy : enemies) {
        enemy->draw(window);
    }
}

void SceneLevel::drawPlayer (sf::RenderWindow& window) {
    player.draw(window);
}

void SceneLevel::drawColliders (sf::RenderWindow& window) {
    for (const Collider& collider : colliders) {
        collider.drawColliderBounds(window, sf::Color::Green);
    }
    for (const auto& enemy : enemies) {
        enemy->getCollider().drawColliderBounds(window, sf::Color::Red);
    }
    player.getCollider().drawColliderBounds(window, sf::Color::Blue);
}