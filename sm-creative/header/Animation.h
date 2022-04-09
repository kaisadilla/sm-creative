#pragma once

#include <SFML/Graphics.hpp>

#include "root.h"

class Animation {
private:
    i32 frameCount;
    i32 currentFrame = 0;
    f32 timeSinceLastFrame = 0.f;

    //bool animate = true;
    std::vector<f32> frameTimes;
    std::vector<sf::IntRect> frameSlices;

public:
    Animation(const std::vector<f32>& frameTimes, const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize);
    Animation(const f32& frameTime, const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize);
    Animation(const Animation& animation);

    void onUpdate(const f32 deltaTime, const f32 speed);
    void reset();

    inline sf::IntRect getCurrentSlice () const {
        return frameSlices[currentFrame];
    }

private:
    void initialize(const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize);
};