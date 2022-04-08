#include "Animation.h"

Animation::Animation (const Animation& animation) :
    frameCount(animation.frameCount),
    currentFrame(animation.currentFrame),
    timeSinceLastFrame(animation.timeSinceLastFrame),
    frameTimes(animation.frameTimes),
    frameSlices(animation.frameSlices)
{}

Animation::Animation (const std::vector<f32>& frameTimes, const std::vector<ui32>& frames, const uvec2& textureSize, const uvec2& sliceSize) :
    frameTimes(frameTimes)
{
    if (frameTimes.size() != frames.size()) {
        std::cerr << "[Animation - Error] The amount of frames given and the amount of frametimes given are not the same." << "\n";
    }

    initialize(frames, textureSize, sliceSize);
}

Animation::Animation (const f32& frameTime, const std::vector<ui32>& frames, const uvec2& textureSize, const uvec2& sliceSize) :
    frameTimes(frames.size())
{
    for (size_t i = 0; i < frameTimes.size(); i++) {
        frameTimes[i] = frameTime;
    }

    initialize(frames, textureSize, sliceSize);
}

void Animation::onUpdate (const f32& deltaTime) {
    timeSinceLastFrame += deltaTime;

    while (timeSinceLastFrame >= frameTimes[currentFrame]) {
        timeSinceLastFrame -= frameTimes[currentFrame];

        currentFrame++;

        if (currentFrame >= frameCount) {
            currentFrame = 0;
        }
    }
}

void Animation::initialize (const std::vector<ui32>& frames, const uvec2& textureSize, const uvec2& sliceSize) {
    const ui32 widthInFrames = textureSize.x / sliceSize.x;
    const ui32 heightInFrames = textureSize.y / sliceSize.y;
    const ui32 totalFrames = widthInFrames * heightInFrames;

    for (const ui32& frame : frames) {
        if (frame >= totalFrames) {
            std::cerr << "[Animation - Error] The frame given (" << frame << ") is ouside the bounds of the texture." << "\n";
        }

        ui32 xStart = frame % widthInFrames;
        ui32 yStart = frame / widthInFrames;

        frameSlices.push_back(sf::IntRect(xStart * sliceSize.x, yStart * sliceSize.y, sliceSize.x, sliceSize.y));
    }

    frameCount = frameSlices.size();
}
