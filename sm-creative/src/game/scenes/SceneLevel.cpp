#include "game/scenes/SceneLevel.h"

SceneLevel::SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const Level& level) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    levelTileWidth(level.getLevelWidth()),
    levelTileHeight(level.getLevelHeight()),
    player(vec2(16.f, 16.f)),
    foregroundLayer(level.getForegroundPlane())
{
    for (i32 x = 0; x < levelTileWidth; x++) {
        for (i32 y = 0; y < levelTileHeight; y++) {
            WorldTile worldTile = foregroundLayer.getAt(x, y);
            if (!worldTile.getTile()->isAirTile()) {
                colliders.push_back(Collider(vec2(x * 16 + 8, y * 16 + 8), vec2(8, 8)));
            }
        }
    }
}

void SceneLevel::onEnter () {
    camera = Camera(uvec2(foregroundLayer.getWidth() * 16, foregroundLayer.getHeight() * 16), uvec2(windowWidth, windowHeight));

    __texBackground.loadFromFile("res/sprites/backgrounds/default_0.png");
    
    __background.setTexture(__texBackground);

    __texPlayer.loadFromFile("res/sprites/characters/mario.png");

    player.setTexture(__texPlayer);

    //__collider.setCenter(vec2(14.f * 16.f + 8.f, 19.f * 16.f + 8.f));
    //__collider.setDistanceToEdge(vec2(8.f, 8.f));
}

void SceneLevel::onUpdate (const f32 deltaTime) {
    player.onUpdate(deltaTime, colliders);
    camera.updatePosition(player.getPosition());
}

void SceneLevel::onDraw (sf::RenderWindow& window) {
    window.draw(__background);

    window.setView(camera.getView());
    drawLevel(window);
    drawMobs(window);
    drawPlayer(window);
    drawColliders(window);
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

}

void SceneLevel::drawPlayer (sf::RenderWindow& window) {
    player.draw(window, vec2(0, 0));
}

void SceneLevel::drawColliders (sf::RenderWindow& window) {
    player.getCollider().drawColliderBounds(window);
    for (Collider collider : colliders) {
        collider.drawColliderBounds(window);
    }
}