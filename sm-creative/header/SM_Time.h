#pragma once

#include "root.h"
#include <SFML/Graphics.hpp>

class Time {
private:
    inline static sf::Clock clock;
    inline static f32 time;
    inline static f32 deltaTime;

public:
    static void start();
    static void update();

public:
    static inline f32 getTime () {
        return time;
    }
    static inline f32 getDeltaTime () {
        return deltaTime;
    }
};