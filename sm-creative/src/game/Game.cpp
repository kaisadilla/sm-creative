#include "game/Game.h"

Game::Game () :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "M-Guy editable", sf::Style::Close),
    scene(WINDOW_WIDTH, WINDOW_HEIGHT, Assets::levels["level1-1"])
{}

void Game::initialize () {
    Time::start();
    fpsCounter.setUpdateTime(0.1f);

    window.close();
    window.create(sf::VideoMode(WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2), "M-Guy editable", sf::Style::Close);
    window.setFramerateLimit(180);

    setupDebugInfo();

    sf::Listener::setGlobalVolume(50.f);

    scene.onEnter();
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
    scene.onUpdate();
}

void Game::draw () {
    window.clear();
    scene.onDraw(window);

    if (Debug::showDebugInfo) drawDebugInfo();

    window.display();
}

void Game::lateUpdate () {
    scene.onLateUpdate();
}

bool Game::isOpen () {
    return window.isOpen();
}

void Game::setupDebugInfo () {
    if (!debugFont.loadFromFile("res/fonts/CascadiaMono.ttf")) {
        std::cout << "ERROR LOADING CASCADIA MONO." << "\n";
    }

    infoFps.setFont(debugFont);
    infoFps.setString("FPS: 0");
    infoFps.setPosition(8.f, 2.f);
    infoFps.setCharacterSize(12);
    infoFps.setFillColor(sf::Color::White);
    infoFps.setStyle(sf::Text::Regular);
}

void Game::fixedUpdate () {
    scene.onFixedUpdate();
}

void Game::updateFps () {
    fpsCounter.count();

    if (fpsCounter.isUpdated()) {
        infoFps.setString("FPS: " + std::to_string(fpsCounter.getFps()));
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
            if (evt.key.code == sf::Keyboard::Key::F3) {
                Debug::showDebugInfo = !Debug::showDebugInfo;
            }
            else if (evt.key.code == sf::Keyboard::Key::F4) {
                Debug::drawCollisions = !Debug::drawCollisions;
            }
        }
    }
}

void Game::drawDebugInfo () {
    window.draw(infoFps);
}
