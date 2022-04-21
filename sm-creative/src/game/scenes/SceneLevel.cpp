#include "game/scenes/SceneLevel.h"
#include "entities/enemies.h"
#include "assets/data/LevelData.h"

SceneLevel::SceneLevel() :
    windowWidth(0),
    windowHeight(0),
    levelTileWidth(0),
    levelTileHeight(0),
    backgroundLayer(0, 0),
    foregroundLayer(0, 0),
    player(this, vec2(16.f, 16.f))
{}

SceneLevel::SceneLevel(const ui32 windowWidth, const ui32 windowHeight, const LevelData& level) :
    windowWidth(windowWidth),
    windowHeight(windowHeight),
    levelTileWidth(0),
    levelTileHeight(0),
    player(this, vec2(16.f, 16.f)),
    backgroundLayer(0, 0),
    foregroundLayer(0, 0)
{
    //for (ui32 x = 0; x < levelTileWidth; x++) {
    //    for (ui32 y = 0; y < levelTileHeight; y++) {
    //        WorldTile& worldTile = foregroundLayer.getAt(x, y);
    //        // TODO: This may be better as part of the world tile. The scenelevel'd only keep a vector
    //        // of references to worldtiles that have colliders.
    //        if (!worldTile.getTile()->isAirTile() && worldTile.getTile()->hasCollider()) {
    //            colliders.push_back(Collider(&worldTile, vec2(x * 16.f, y * 16.f), vec2(8.f, 8.f), vec2(8.f, 8.f)));
    //        }
    //    }
    //}
    //
    //for (auto& enemyData : level.getEnemies()) {
    //    Mob* enemy = createEnemyForLevel(enemyData, this);
    //    if (enemy != nullptr) {
    //        nextId = std::max(nextId, enemy->getId());
    //        enemies.push_back(enemy);
    //    }
    //}
    //
    //sound_pause.setBuffer(Assets::sound_pause);
    //texPause.loadFromFile("res/sprites/ui/pause.png");
    //spritePause.setTexture(texPause);
    //spritePause.setTextureRect(sf::IntRect(ivec2(0, 0), (ivec2)texPause.getSize()));
}

SceneLevel::~SceneLevel () {
    for (auto enemy : enemies) {
        delete enemy;
    }
    //for (auto item : items) {
    //    delete item;
    //}
}

void SceneLevel::onEnter () {
    camera = Camera(uvec2(foregroundLayer.getWidth() * 16, foregroundLayer.getHeight() * 16), uvec2(windowWidth, windowHeight));

    __texBackground.loadFromFile("res/sprites/backgrounds/default_0.png");
    
    __background.setTexture(__texBackground);
    __background.setScale(vec2(2.f, 2.f));

    player.setSprite("mario", vec2(32, 32));
    player.setPosition(vec2(0.f, 22.f * 16.f));
    player.initializeDefaultSpriteAndColliderSizes(vec2(32, 32), sf::IntRect(11, 17, 10, 15));

    levelMusic.openFromFile("res/music/overworld.wav");
    //levelMusic.openFromFile("res/music/sml2_athletic.wav");
    levelMusic.setLoop(true);
    levelMusic.setVolume(50.f);
    levelMusic.play();

    //Item* item = new SuperMushroom(this, vec2(16, 16), true);
    //items.push_back(item);
    items.emplace_back(std::make_unique<SuperMushroom>(SuperMushroom(this, vec2(16, 16), true)));
    items[0]->setId(333);
    items[0]->setSprite("mushroom", vec2(16, 16));
    items[0]->initializeDefaultSpriteAndColliderSizes(vec2(16, 16), sf::IntRect(0, 0, 16, 16));
    items[0]->setPosition(vec2(5 * 16.f, 16 * 16.f));

    for (auto& item : items) {
        item->onStart();
    }
    for (auto& enemy : enemies) {
        enemy->onStart();
    }
}

void SceneLevel::onUpdate () {
    for (auto& item : items) {
        item->onUpdate();
    }
    for (auto& enemy : enemies) {
        enemy->onUpdate();
    }

    player.onUpdate();
    camera.updatePosition(player.getPixelPosition());

    deleteDisposedEnemies();
}

void SceneLevel::onFixedUpdate () {
    for (auto& item : items) {
        item->onFixedUpdate();
        item->checkCollisionsWithTiles(colliders);
    }
    for (auto& enemy : enemies) {
        enemy->onFixedUpdate();
    }

    for (i32 i = 0; i < enemies.size(); i++) {
        enemies[i]->checkCollisionsWithTiles(colliders);
        enemies[i]->checkCollisionWithEnemies(enemies, i + 1);
    }

    player.onFixedUpdate();
    player.checkCollisionsWithTiles(colliders);
    player.checkCollisionWithItems(items);
    player.checkCollisionWithEnemies(enemies);
}

void SceneLevel::onDraw (sf::RenderWindow& window) {
    window.draw(__background);

    window.setView(camera.getView());
    drawLevel(window);
    drawItems(window);
    drawMobs(window);
    drawPlayer(window);

    if (Debug::drawCollisions) drawColliders(window);
    if (Debug::drawDebugInfo) drawDebugInfo(window);

    window.setView(window.getDefaultView());

    if (isLevelPaused) {
        spritePause.setPosition(((vec2)window.getSize() / 2.f) - (((vec2)texPause.getSize() * 2.f) / 2.f));
        window.draw(spritePause);
    }
}

void SceneLevel::onLateUpdate () {

}

void SceneLevel::onEvent (const sf::Event& evt) {
    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == sf::Keyboard::Key::Pause || evt.key.code == sf::Keyboard::Key::P) {
            if (isLevelPaused) {
                Time::resume();
                isLevelPaused = false;
            }
            else {
                Time::pause();
                isLevelPaused = true;
            }

            sound_pause.play();
        }
    }
}

void SceneLevel::deleteDisposedEnemies () {
    //enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
    auto& itEnemies = enemies.begin();

    while (itEnemies != enemies.end()) {
        if ((*itEnemies)->getDisposePending()) {
            delete (*itEnemies);
            itEnemies = enemies.erase(itEnemies);
        }
        else {
            itEnemies++;
        }
    }

    auto& itItems = items.begin();
    while (itItems != items.end()) {
        if ((*itItems)->getDisposePending()) {
            //delete (*itItems);
            itItems = items.erase(itItems);
        }
        else {
            itItems++;
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

void SceneLevel::drawItems(sf::RenderWindow& window) {
    for (const auto& item : items) {
        item->draw(window);
    }
}

void SceneLevel::drawPlayer (sf::RenderWindow& window) {
    player.draw(window);
}

void SceneLevel::drawColliders (sf::RenderWindow& window) {
    for (const Collider& collider : colliders) {
        collider.drawColliderBounds(window, sf::Color::Green);
    }
    for (const auto& item : items) {
        item->getCollider().drawColliderBounds(window);
    }
    for (const auto& enemy : enemies) {
        enemy->getCollider().drawColliderBounds(window);
    }
    player.getCollider().drawColliderBounds(window);
}

void SceneLevel::drawDebugInfo (sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy->drawDebugInfo(window);
    }
}