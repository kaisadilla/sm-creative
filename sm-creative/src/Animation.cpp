#include "Animation.h"

Animation::Animation (const Animation& animations) :
    frameCount(animations.frameCount),
    currentFrame(animations.currentFrame),
    timeSinceLastFrame(animations.timeSinceLastFrame),
    frameTimes(animations.frameTimes),
    frameSlices(animations.frameSlices),
    frameSlicesMirrored(animations.frameSlicesMirrored)
{}

void Animation::reset () {
    currentFrame = 0;
    timeSinceLastFrame = 0.f;
}

Animation::Animation (const std::vector<f32>& frameTimes, const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize) :
    frameTimes(frameTimes)
{
    if (frameTimes.size() != frames.size()) {
        std::cerr << "[Animation - Error] The amount of frames given and the amount of frametimes given are not the same." << "\n";
    }

    initialize(frames, slices, sliceSize);
}

Animation::Animation (const f32& frameTime, const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize) :
    frameTimes(frames.size())
{
    for (size_t i = 0; i < frameTimes.size(); i++) {
        frameTimes[i] = frameTime;
    }

    initialize(frames, slices, sliceSize);
}

void Animation::onUpdate (const f32 deltaTime, const f32 speed) {
    timeSinceLastFrame += deltaTime * speed;

    while (timeSinceLastFrame >= frameTimes[currentFrame]) {
        timeSinceLastFrame -= frameTimes[currentFrame];

        currentFrame++;

        if (currentFrame >= frameCount) {
            currentFrame = 0;
        }
    }
}

void Animation::initialize (const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize) {
    const ui32 totalFrames = slices.x * slices.y;

    for (const ui32& frame : frames) {
        if (frame >= totalFrames) {
            std::cerr << "[Animation - Error] The frame given (" << frame << ") is ouside the bounds of the texture." << "\n";
        }

        ui32 xStart = frame % slices.x;
        ui32 yStart = frame / slices.x;

        frameSlices.push_back(sf::IntRect(xStart * sliceSize.x, yStart * sliceSize.y, sliceSize.x, sliceSize.y));
        frameSlicesMirrored.push_back(sf::IntRect((xStart + 1) * sliceSize.x, yStart * sliceSize.y, -sliceSize.x, sliceSize.y));
    }

    frameCount = frameSlices.size();
}
