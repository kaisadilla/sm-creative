#pragma once

#include "root.h"
#include <SFML/Graphics.hpp>

class Time {
private:
    inline static sf::Clock clock;
    inline static f32 time = 0;
    inline static f32 deltaTime = 0;

    inline static f32 timeScale = 1.f;
    inline static bool paused = true;

public:
    static void start();
    static void update();

public:
    static inline f32 getTime () {
        return time;
    }

    /// <summary>
    /// Returns the amount of time, in seconds, since the last update.
    /// </summary>
    static inline f32 getDeltaTime () {
        return deltaTime;
    }

    static inline f32 getTimeScale () {
        return timeScale;
    }

    static inline bool getPaused () {
        return paused;
    }

    static inline void setTimeScale (const f32 timeScale) {
        Time::timeScale = timeScale;
    }

    static inline void pause () {
        Time::paused = true;
    }

    static inline void resume () {
        Time::paused = false;
    }

    static inline void pauseOrResume () {
        Time::paused = !Time::paused;
    }
};