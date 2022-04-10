#include "SM_Time.h"

void Time::start () {
    time = 0;
    deltaTime = 0;
}


void Time::update () {
    f32 newTime = clock.getElapsedTime().asSeconds();
    deltaTime = newTime - time;
    time = newTime;
}