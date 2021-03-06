#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "assets/Assets.h"
#include "Debug.h"
#include "SM_Time.h"
#include "JobManager.h"
#include "utils/FpsCounter.h"
#include "game/scenes/Scene.h"

class Game {
private:
    static constexpr ui32 WINDOW_WIDTH = WINDOW_WIDTH_IN_TILES * PIXELS_PER_TILE;
    static constexpr ui32 WINDOW_HEIGHT = WINDOW_HEIGHT_IN_TILES * PIXELS_PER_TILE;

public:
    /**********
     * SCORES *
     **********/
    i32 lives = 5;
    i32 coins = 0;
    i32 score = 0;
    i32 yoshiCoins = 0;
    i32 endLevelItems[3] = { 0, 0, 0 };

private:
    sf::RenderWindow window;
    f32 cumulativeFixedTime = 0.f;

    // FPS counter.
    bool cappedFps = true;
    FpsCounter fpsCounter;
    f32 timeSinceLastFpsUpdate = 0.f;

    std::unique_ptr<Scene> scene;

    // Debug information;
    sf::RectangleShape debugBackground;
    sf::Font debugFont;
    sf::Text infoFps;
    sf::Text infoTime;
    sf::Text infoTimeScale;

public:
    Game();

    void initialize();

    void update();
    void draw();
    void lateUpdate();

    bool isOpen();

private:
    void setupDebugInfo();
    void fixedUpdate();
    void updateFps();
    void pollEvents();

    void drawDebugInfo();
};