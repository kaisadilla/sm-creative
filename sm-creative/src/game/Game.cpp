#include "game/Game.h"

Game::Game ()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SuperM Creative", sf::Style::Close),
    deltaTime(deltaTime)
{
    Level level;
    level.__build_level_from_json("res/data/level1-1.json");
    scene = SceneLevel(WINDOW_WIDTH, WINDOW_HEIGHT, level);
}

void Game::initialize () {
    fpsCounter.setUpdateTime(0.1f);
    window.setFramerateLimit(180);

    scene.onEnter();
    //window.setSize(uvec2(WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2));

    if (!__font.loadFromFile("res/fonts/CascadiaMono.ttf")) {
        std::cout << "ERROR LOADING CASCADIA MONO." << "\n";
    }
}

void Game::update () {
    deltaTime = clock.restart().asSeconds();
    updateFps();

    sf::Event evt;

    while (window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            window.close();
        }
    }

    scene.onUpdate(deltaTime);
}

void Game::draw () {
    window.clear();
    scene.onDraw(window);

    // TODO: REMOVE THIS AND MAKE IT PART OF THE DEBUG UI.
    string fps = std::to_string(fpsCounter.getFps());
    string ms = std::to_string(fpsCounter.getLatency() * 1000.f);

    string title = fps + " fps [" + ms + " ms]";

    sf::Text text;
    text.setFont(__font);
    text.setString(title);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);
    window.draw(text);

    window.display();
}

void Game::lateUpdate () {
    scene.onLateUpdate();
}

bool Game::isOpen () {
    return window.isOpen();
}

void Game::updateFps () {
    fpsCounter.count(deltaTime);

    if (fpsCounter.isUpdated()) {
        string fps = std::to_string(fpsCounter.getFps());
        string ms = std::to_string(fpsCounter.getLatency() * 1000.f);

        string title = "SuperM Creative - " + fps + " fps [" + ms + " ms]";
        window.setTitle(title);
    }
}
