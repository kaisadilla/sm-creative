#include "SM_Time.h"

void Time::start () {
    clock.restart();
    time = 0;
    deltaTime = 0;
    paused = false;
}


void Time::update () {
    // we still need to restart the clock even if time is paused.
    deltaTime = clock.restart().asSeconds() * timeScale;

    if (paused) {
        deltaTime = 0.f;
    }

    time += deltaTime;

    //f32 newTime = clock.getElapsedTime().asSeconds();
    //deltaTime = newTime - time;
    //time = newTime;
}