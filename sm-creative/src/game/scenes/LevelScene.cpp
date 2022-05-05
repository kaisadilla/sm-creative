#include <fstream>

#include "game/scenes/LevelScene.h"
#include "game/Game.h"

#include "vfx/EarnedCoinParticle.h"

LevelScene::LevelScene () {}

LevelScene::~LevelScene () {
    music.stop();
    //std::cout << "Deleted level" << "\n";
}

void LevelScene::onEnter () {
    camera = Camera(uvec2(getPixelWidth(), getPixelHeight()), uvec2(windowSize.x / windowZoom.x, windowSize.y / windowZoom.y));
    __TEMPORARY_initialize_player();

    for (const auto& tile : foregroundLayer) {
        tile->onStart();
    }
    for (const auto& tile : backgroundLayer) {
        tile->onStart();
    }
    for (const auto& entity : entities) {
        entity->start();
    }

    __TEMPORARY_sound_pause.setBuffer(Assets::sound_pause);
    __TEMPORARY_texPause.loadFromFile("res/sprites/ui/pause.png");
    __TEMPORARY_spritePause.setTexture(__TEMPORARY_texPause);
    __TEMPORARY_spritePause.setTextureRect(sf::IntRect(ivec2(0, 0), (ivec2)__TEMPORARY_texPause.getSize()));

    ui.__TEMPORARY_initialize_ui();
    ui.__TEMPORARY_update_world("1");
    ui.__TEMPORARY_update_lives(game->lives);
    ui.__TEMPORARY_update_coins(game->coins);
    ui.__TEMPORARY_update_time((i32)timeLeft);
    ui.__TEMPORARY_update_score(game->score);

    initializeBackground();
    music.play();
}

void LevelScene::onUpdate () {
    timeLeft -= Time::getDeltaTime();

    for (const auto& tile : foregroundLayer) {
        tile->onUpdate();
    }
    for (const auto& tile : backgroundLayer) {
        tile->onUpdate();
    }
    for (const auto& entity : entities) {
        entity->update();
    }
    for (const auto& particle : particles) {
        particle->onUpdate();
    }

    player.update();
    camera.updatePosition(player.getPixelPosition());

    deleteDisposedObjects();
    updateBackgroundPosition();

    ui.__TEMPORARY_update_time(timeLeft);
}

void LevelScene::onFixedUpdate () {
    for (const auto& entity : entities) {
        entity->fixedUpdate();
    }
    for (i32 i = 0; i < entities.size(); i++) {
        entities[i]->checkCollisionWithTiles(foregroundLayer);
        entities[i]->checkCollisionWithEntities(entities, i + 1);
    }

    player.fixedUpdate();
    player.checkCollisionWithTiles(foregroundLayer);
    player.checkCollisionWithEntities(entities);
}

void LevelScene::onLateUpdate () {

}

void LevelScene::onDraw (sf::RenderWindow& window) {
    window.draw(backgroundImage);

    window.setView(camera.getView());
    drawLayer(window, backgroundLayer);
    drawEntities(window, true);
    drawLayer(window, foregroundLayer);
    drawEntities(window, false);
    drawPlayer(window);
    drawParticles(window);

    if (Debug::drawCollisions) drawColliders(window);
    if (Debug::drawDebugInfo) drawDebugInfo(window);

    window.setView(window.getDefaultView());

    ui.__TEMPORARY_draw_ui(window);

    // TODO: Move this into a drawUI() or something.
    if (isLevelPaused) {
        __TEMPORARY_spritePause.setPosition(((vec2)window.getSize() / 2.f) - (((vec2)__TEMPORARY_texPause.getSize() * 2.f) / 2.f));
        window.draw(__TEMPORARY_spritePause);
    }
}

void LevelScene::onEvent (const sf::Event& evt) {
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

            __TEMPORARY_sound_pause.play();
        }
    }
}

i32 LevelScene::addLives (const i32 lives) {
    game->lives += lives;
    ui.__TEMPORARY_update_lives(game->lives);
    return game->lives;
}

i32 LevelScene::addCoins (const i32 coins) {
    game->coins += coins;
    ui.__TEMPORARY_update_coins(game->coins);
    return game->coins;
}

i32 LevelScene::addScore (const i32 score) {
    game->score += score;
    ui.__TEMPORARY_update_score(game->score);
    return game->score;
}

void LevelScene::instantiateParticle (std::unique_ptr<Particle>& particle) {
    particle->onStart();
    particles.push_back(std::move(particle));
}

void LevelScene::instantiateEntity (std::unique_ptr<Entity>& entity) {
    entity->setLevel(this);
    entity->start();
    entities.push_back(std::move(entity));
}

void LevelScene::loadBackground (const string& name) {
    backgroundTexture.loadFromFile("res/sprites/backgrounds/" + name + ".png");
    backgroundImage.setTexture(backgroundTexture);
    backgroundImage.setScale(vec2(2.f, 2.f));
}

void LevelScene::loadMusic (const string& name) {
    music.openFromFile("res/music/" + name + ".wav");
    music.setLoop(true);
    music.setVolume(50.f);
}

void LevelScene::drawLayer (sf::RenderWindow& window, std::vector<std::unique_ptr<Tile>>& layer) {
    for (const auto& tile : layer) {
        tile->draw(window);
    }
}

void LevelScene::drawEntities (sf::RenderWindow& window, const bool entitiesBeforeForeground) {
    for (const auto& entity : entities) {
        if (entity->getDrawBeforeForeground() == entitiesBeforeForeground) {
            entity->draw(window);
        }
    }
}

void LevelScene::drawPlayer (sf::RenderWindow& window) {
    player.draw(window);
}

void LevelScene::drawParticles (sf::RenderWindow& window) {
    for (const auto& particle : particles) {
        particle->draw(window);
    }
}

void LevelScene::drawColliders (sf::RenderWindow& window) {
    for (const auto& tile : foregroundLayer) {
        tile->getCollider().drawColliderBounds(window);
    }
    for (const auto& entity : entities) {
        entity->getCollider().drawColliderBounds(window);
    }
    player.getCollider().drawColliderBounds(window);
}

void LevelScene::drawDebugInfo (sf::RenderWindow& window) {
    for (const auto& entity : entities) {
        entity->drawDebugInfo(window);
    }
}

void LevelScene::deleteDisposedObjects () {
    auto& itEntities = entities.begin();

    while (itEntities != entities.end()) {
        if ((*itEntities)->getDisposePending()) {
            itEntities = entities.erase(itEntities);
        }
        else {
            itEntities++;
        }
    }

    auto& itParticles = particles.begin();

    while (itParticles != particles.end()) {
        if ((*itParticles)->getDisposePending()) {
            itParticles = particles.erase(itParticles);
        }
        else {
            itParticles++;
        }
    }
}

void LevelScene::initializeBackground () {
    // TODO: This is hardcoded to scale to 2x zoom.
    auto& bgSize = backgroundTexture.getSize();
    // TODO: Will underflow if the size of the window is bigger than the size of the background texture.
    backgroundParallaxMaxX = bgSize.x - (windowSize.x / 2);
    backgroundParallaxMaxY = bgSize.y - (windowSize.y / 2);
    levelParallaxMaxX = getPixelWidth() - (windowSize.x / 2);
    levelParallaxMaxY = getPixelHeight() - (windowSize.y / 2);
}

void LevelScene::updateBackgroundPosition() {
    auto& topLeft = camera.getTopLeft();

    const i32 xTop = (i32)math::lerp(0, backgroundParallaxMaxX, topLeft.x / levelParallaxMaxX);
    const i32 yTop = (i32)math::lerp(0, backgroundParallaxMaxY, topLeft.y / levelParallaxMaxY);

    backgroundImage.setTextureRect(sf::IntRect(xTop, yTop, windowSize.x / 2, windowSize.y / 2));
}

void LevelScene::__TEMPORARY_initialize_player () {
    player.setDefaultSizes(vec2(32.f, 32.f), vec2(32.f, 32.f), sf::IntRect(11, 18, 10, 14));
    player.setGridPosition(ivec2(0.f, 22.f));
    player.__TEMPORARY_set_sprite_by_filename("mario", vec2(32, 32));
    player.__TEMPORARY_initialize_animations();
    player.setLevel(this);
}