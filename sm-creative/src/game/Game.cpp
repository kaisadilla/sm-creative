#include "game/Game.h"

Game::Game ()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SuperM Creative", sf::Style::Close),
    deltaTime(deltaTime)
{
    scene = SceneLevel(WINDOW_WIDTH, WINDOW_HEIGHT, Assets::levels["level1-1"]);
}

void Game::initialize () {
    fpsCounter.setUpdateTime(0.1f);
    window.setFramerateLimit(180);

    scene.onEnter();
    window.setSize(uvec2(WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2));
    // Correct way to scale the window and adjust what we want scaled (with view).
    //window.close();
    //window.create(sf::VideoMode(WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2), "SuperM Creative", sf::Style::Close);
    

    if (!__font.loadFromFile("res/fonts/CascadiaMono.ttf")) {
        std::cout << "ERROR LOADING CASCADIA MONO." << "\n";
    }
}

void Game::update () {
    deltaTime = clock.restart().asSeconds();
    // if a frame took more than 0.25 seconds to complete, we discard it because else unexpected results may occur.
    // this may not be necessary if physics are moved to a fixed update loop.
    if (deltaTime > 0.25f) {
        deltaTime = 0;
    }
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
    //string fps = std::to_string(fpsCounter.getFps());
    //string ms = std::to_string(fpsCounter.getLatency() * 1000.f);
    //
    //string title = fps + " fps [" + ms + " ms]";
    //
    //sf::Text text;
    //text.setFont(__font);
    //text.setString(title);
    //text.setCharacterSize(12);
    //text.setFillColor(sf::Color::White);
    //text.setStyle(sf::Text::Regular);
    //window.draw(text);

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
