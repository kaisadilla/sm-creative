#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"
#include "Assets.h"
#include "Debug.h"
#include "SM_Time.h"
#include "game/scenes/SceneLevel.h"
#include "utils/FpsCounter.h"

class Game {
private:
    static constexpr ui32 WINDOW_WIDTH = WINDOW_WIDTH_IN_TILES * PIXELS_PER_TILE;
    static constexpr ui32 WINDOW_HEIGHT = WINDOW_HEIGHT_IN_TILES * PIXELS_PER_TILE;
private:
    sf::RenderWindow window;
    f32 cumulativeFixedTime = 0.f;

    // FPS counter.
    FpsCounter fpsCounter;
    f32 timeSinceLastFpsUpdate = 0.f;

    SceneLevel scene;

    // Debug information;
    sf::Font debugFont;
    sf::Text infoFps;

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