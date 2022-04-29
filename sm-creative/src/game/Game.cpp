#include "game/Game.h"
#include "assets/data/LevelData.h"
#include "game/scenes/LevelScene.h"
#include "game/scenes/LevelReader.h"

Game::Game () :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "M-Guy editable", sf::Style::Close)
{}

void Game::initialize () {
    fpsCounter.setUpdateTime(0.1f);

    window.close();
    window.create(sf::VideoMode(WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2), "M-Guy editable", sf::Style::Close);
    window.setFramerateLimit(180);

    setupDebugInfo();

    sf::Listener::setGlobalVolume(50.f);

    scene = std::unique_ptr<LevelScene>(LevelReader::loadLevel("level1-1"));

    scene->setWindowSize(window.getSize(), vec2(2.f, 2.f));
    scene->onEnter();
    Time::start();

    uiFont.loadFromFile("res/bitfonts/smb3-font.json");
    uiText.setFont(uiFont);
    uiText.setPosition(vec2(150, 150));
    uiText.setString("092138");
}

void Game::update () {
    Time::update();
    JobManager::onUpdate();

    cumulativeFixedTime += Time::getDeltaTime();

    while (cumulativeFixedTime > SECONDS_PER_FIXED_UPDATE) {
        fixedUpdate();
        cumulativeFixedTime -= SECONDS_PER_FIXED_UPDATE;
    }

    updateFps();
    pollEvents();
    scene->onUpdate();
}

void Game::draw () {
    window.clear();
    scene->onDraw(window);

    if (Debug::showDebugInfo) drawDebugInfo();

    window.draw(uiText);

    window.display();
}

void Game::lateUpdate () {
    scene->onLateUpdate();
}

bool Game::isOpen () {
    return window.isOpen();
}

void Game::setupDebugInfo () {
    if (!debugFont.loadFromFile("res/fonts/CascadiaMono.ttf")) {
        std::cout << "ERROR LOADING CASCADIA MONO." << "\n";
    }

    infoFps.setFont(debugFont);
    infoFps.setString("FPS: 0" + cappedFps ? "[capped]" : "");
    infoFps.setPosition(8.f, 2.f);
    infoFps.setCharacterSize(12);
    infoFps.setFillColor(sf::Color::White);
    infoFps.setStyle(sf::Text::Regular);

    infoTime.setFont(debugFont);
    infoTime.setString("Time: 0.00");
    infoTime.setPosition(8.f, 14.f);
    infoTime.setCharacterSize(12);
    infoTime.setFillColor(sf::Color::White);
    infoTime.setStyle(sf::Text::Regular);

    infoTimeScale.setFont(debugFont);
    infoTimeScale.setString("Time scale: 0.00 [paused]");
    infoTimeScale.setPosition(8.f, 26.f);
    infoTimeScale.setCharacterSize(12);
    infoTimeScale.setFillColor(sf::Color::White);
    infoTimeScale.setStyle(sf::Text::Regular);
}

void Game::fixedUpdate () {
    scene->onFixedUpdate();
}

void Game::updateFps () {
    fpsCounter.count();

    if (fpsCounter.isUpdated()) {
        infoFps.setString("FPS: " + std::to_string(fpsCounter.getFps()) + (cappedFps ? " [capped]" : ""));
    }

    //if (fpsCounter.isUpdated()) {
    //    string fps = std::to_string(fpsCounter.getFps());
    //    string ms = std::to_string(fpsCounter.getLatency() * 1000.f);
    //
    //    string title = "SuperM Creative - " + fps + " fps [" + ms + " ms]";
    //    window.setTitle(title);
    //}
}

void Game::pollEvents () {
    sf::Event evt;

    while (window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            window.close();
        }
        else if (evt.type == sf::Event::KeyPressed) {
            if (evt.key.code == sf::Keyboard::Key::F1) {
                Time::pauseOrResume();
            }
            else if (evt.key.code == sf::Keyboard::Key::F2) {
                scene.reset();
                scene = std::unique_ptr<LevelScene>(LevelReader::loadLevel("level1-1"));

                scene->setWindowSize(window.getSize(), vec2(2.f, 2.f));
                scene->onEnter();
            }
            else if (evt.key.code == sf::Keyboard::Key::F3) {
                Debug::showDebugInfo = !Debug::showDebugInfo;
            }
            else if (evt.key.code == sf::Keyboard::Key::F4) {
                Debug::drawCollisions = !Debug::drawCollisions;
            }
            else if (evt.key.code == sf::Keyboard::Key::F5) {
                Debug::drawDebugInfo = !Debug::drawDebugInfo;
            }
            else if (evt.key.code == sf::Keyboard::Key::F10) {
                if (cappedFps) {
                    window.setFramerateLimit(0);
                }
                else {
                    window.setFramerateLimit(180);
                }

                cappedFps = !cappedFps;
            }
            else if (evt.key.code == sf::Keyboard::Key::F11) {
                if (Time::getTimeScale() == 1.f) {
                    Time::setTimeScale(0.5f);
                }
                else if (Time::getTimeScale() == 0.5f) {
                    Time::setTimeScale(0.25f);
                }
                else if (Time::getTimeScale() == 0.25f) {
                    Time::setTimeScale(0.125f);
                }
                else {
                    Time::setTimeScale(1.f);
                }
            }
        }

        scene->onEvent(evt);
    }
}

void Game::drawDebugInfo () {
    string strTime = "Time: " + std::to_string(Time::getTime());
    string strTimeScale = "Time scale: " + std::to_string(Time::getTimeScale());
    if (Time::getPaused()) {
        strTimeScale += " [PAUSED]";
    }

    infoTime.setString(strTime);
    infoTimeScale.setString(strTimeScale);

    window.draw(infoFps);
    window.draw(infoTime);
    window.draw(infoTimeScale);
}
