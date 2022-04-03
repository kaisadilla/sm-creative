#pragma once

#include "root.h"

class FpsCounter {
private:
    f32 updateTime = 0;

    // Public data.
    bool updatedLastFrame = false;
    ui32 fps = 0;
    f32 latency = 0;

    // Internal data.
    f32 timeSinceLastUpdate = 0.f;
    ui32 internalFpsCounter = 0;
public:
    /// <summary>
    /// Sets the time it takes for this counter to update its information. A longer time means the counter
    /// is updated less often, but its numbers are more accurate and fluctuate less.
    /// </summary>
    /// <param name="updateTime">The delay (in seconds) before updates for this counter.</param>
    void setUpdateTime(const f32& updateTime);

    /// <summary>
    /// Update this counter. This should called in every frame of the program.
    /// </summary>
    /// <param name="deltaTime">The time it took to complete the last frame.</param>
    void count(const f32& deltaTime);

    /// <summary>
    /// Returns the number of frames per second (FPS) this counter is currently registering.
    /// </summary>
    inline ui32 getFps () {
        return fps;
    }

    /// <summary>
    /// Returns the latency (in seconds) this counter is currently registering. The latency is equal to
    /// the amount of time that has passed since the last two frames registered by this counter.
    /// </summary>
    inline f32 getLatency () {
        return latency;
    }

    /// <summary>
    /// Returns true if this counter was updated in the last frame.
    /// </summary>
    inline bool isUpdated () {
        return updatedLastFrame;
    }
};