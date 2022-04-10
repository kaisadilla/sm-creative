#include "utils/FpsCounter.h"

void FpsCounter::setUpdateTime (const f32& updateTime) {
    this->updateTime = updateTime;
}

void FpsCounter::count () {
    timeSinceLastUpdate += Time::getDeltaTime();
    internalFpsCounter++;

    if (timeSinceLastUpdate > updateTime) {
        fps = (ui32)(internalFpsCounter / timeSinceLastUpdate);
        latency = Time::getDeltaTime() / internalFpsCounter;

        timeSinceLastUpdate -= updateTime;
        timeSinceLastUpdate = std::fmod(timeSinceLastUpdate, 0.1f);
        internalFpsCounter = 0;

        updatedLastFrame = true;
    }
    else {
        updatedLastFrame = false;
    }
}
