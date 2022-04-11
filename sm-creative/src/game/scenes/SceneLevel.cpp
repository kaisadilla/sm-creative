#include "game/scenes/SceneLevel.h"

SceneLevel::SceneLevel() :
    windowWidth(0),
    windowHeight(0),
    levelTileWidth(0),
    levelTileHeight(0),
    backgroundLayer(0, 0),
    foregroundLayer(0, 0),
    player(this, vec2(16.f, 16.f))
{}

SceneLevel::SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const data::Level& level) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    levelTileWidth(level.getWidth()),
    levelTileHeight(level.getHeight()),
    player(this, vec2(16.f, 16.f)),
    backgroundLayer(level.getBackgroundLayer()),
    foregroundLayer(level.getForegroundLayer())
{
    for (ui32 x = 0; x < levelTileWidth; x++) {
        for (ui32 y = 0; y < levelTileHeight; y++) {
            WorldTile& worldTile = foregroundLayer.getAt(x, y);
            // TODO: This may be better as part of the world tile. The scenelevel'd only keep a vector
            // of references to worldtiles that have colliders.
            if (!worldTile.getTile()->isAirTile() && worldTile.getTile()->hasCollider()) {
                colliders.push_back(Collider(&worldTile, vec2(x * 16.f + 8.f, y * 16.f + 8.f), vec2(8.f, 8.f)));
            }
        }
    }

    for (auto& enemy : level.getEnemies()) {
        enemies.push_back(createEnemy(enemy));
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

    player.setSprite("mario", vec2(16, 16));
    player.setPosition(vec2(2.f, 26.f));

    levelMusic.openFromFile("res/music/overworld.wav");
    levelMusic.setLoop(true);
    levelMusic.setVolume(50.f);
    levelMusic.play();

    for (auto& enemy : enemies) {
        enemy->onStart();
    }
}

void SceneLevel::onUpdate () {
    for (auto& enemy : enemies) {
        enemy->onUpdate();
    }

    player.onUpdate();
    camera.updatePosition(player.getPixelPosition());

    deleteDisposedEnemies();
}

void SceneLevel::onFixedUpdate () {
    for (auto& enemy : enemies) {
        enemy->onFixedUpdate();
        enemy->checkCollisionsWithTiles(colliders);
    }

    player.onFixedUpdate();
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
    if (Debug::drawDebugInfo) drawDebugInfo(window);

    window.setView(window.getDefaultView());
}

void SceneLevel::onLateUpdate () {

}

void SceneLevel::deleteDisposedEnemies () {
    //enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
    auto& it = enemies.begin();

    while (it != enemies.end()) {
        if ((*it)->getDisposePending()) {
            it = enemies.erase(it);
        }
        else {
            it++;
        }
    }
}

void SceneLevel::drawLevel (sf::RenderWindow& window) {
    drawLayer(window, backgroundLayer);
    drawLayer(window, foregroundLayer);
}

void SceneLevel::drawLayer (sf::RenderWindow& window, Grid2<WorldTile>& layer) {
    // TODO: Check if sf::View culls tiles outside the viewport or not.
    for (ui32 x = 0; x < levelTileWidth; x++) {
        f32 xPixel = x * PIXELS_PER_TILE;

        for (ui32 y = 0; y < levelTileHeight; y++) {
            f32 yPixel = y * PIXELS_PER_TILE;

            WorldTile worldTile = layer.getAt(x, y);
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

void SceneLevel::drawDebugInfo (sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy->drawDebugInfo(window);
    }
}

Mob* SceneLevel::createEnemy (data::WorldMob mobData) {
    const i32& id = mobData.getId();
    const vec2& size = mobData.getSpriteDimensions();
    const sf::IntRect& defaultCollider = mobData.getCollider("collider");
    const vec2& position = mobData.getPosition();

    Mob* enemy = nullptr;

    if (mobData.getBehavior() == data::Behavior::Goomba) {
        bool avoidsCliffs = mobData.getBehaviorProperty<bool>("avoidsCliffs");
        bool startingDirectionRight = mobData.getBehaviorProperty<bool>("startingDirectionRight");

        enemy = new Goomba(this, size, avoidsCliffs, startingDirectionRight);
    }

    enemy->setId(id);
    enemy->setSprite(mobData.getSprite().c_str(), size);
    enemy->setSpriteAndColliderSizes(size, defaultCollider);
    enemy->setPosition(vec2(position.x * 16.f, position.y * 16.f));

    nextId = std::max(nextId, id);

    return enemy;
}
