#include "animation/DynamicAnimation.h"

DynamicAnimation::DynamicAnimation (const DynamicAnimation& animations) :
    frameCount(animations.frameCount),
    currentFrame(animations.currentFrame),
    timeSinceLastFrame(animations.timeSinceLastFrame),
    frameTimes(animations.frameTimes),
    frameSlices(animations.frameSlices),
    frameSlicesMirrored(animations.frameSlicesMirrored)
{}

DynamicAnimation::~DynamicAnimation () {
    std::cout << "KILLED ANIM \n";
}

void DynamicAnimation::reset () {
    currentFrame = 0;
    timeSinceLastFrame = 0.f;
}

DynamicAnimation::DynamicAnimation (const uvec2& slices, const vec2& sliceSize, const std::vector<f32>& frameTimes, const std::vector<ui32>& frames) :
    frameTimes(frameTimes)
{
    if (frameTimes.size() != frames.size()) {
        std::cerr << "[Animation - Error] The amount of frames given and the amount of frametimes given are not the same." << "\n";
    }

    initialize(frames, slices, sliceSize);
}

DynamicAnimation::DynamicAnimation (const uvec2& slices, const vec2& sliceSize, const f32 frameTime, const std::vector<ui32>& frames) :
    frameTimes(frames.size())
{
    for (size_t i = 0; i < frameTimes.size(); i++) {
        frameTimes[i] = frameTime;
    }

    buildFrameTimeVector(frameTime);
    initialize(frames, slices, sliceSize);
}

DynamicAnimation::DynamicAnimation (const uvec2& slices, const vec2& sliceSize, const f32 frameTime, const std::vector<ui32>& frames, std::function<void()> callback) :
    frameTimes(frames.size()),
    hasCallback(true),
    callback(callback)
{
    buildFrameTimeVector(frameTime);
    initialize(frames, slices, sliceSize);
}

void DynamicAnimation::onUpdate (const f32 deltaTime, const f32 speed) {
    timeSinceLastFrame += deltaTime * speed;

    while (timeSinceLastFrame >= frameTimes[currentFrame]) {
        timeSinceLastFrame -= frameTimes[currentFrame];

        currentFrame++;

        if (currentFrame >= frameCount) {
            if (callback != nullptr) {
                callback();
            }

            if (loop) {
                currentFrame = 0;
            }
        }
    }
}

sf::IntRect DynamicAnimation::getCurrentSlice (const bool mirrored) const {
    return mirrored ? frameSlicesMirrored[currentFrame] : frameSlices[currentFrame];
}

void DynamicAnimation::setLoop(const bool loop) {
    this->loop = loop;
}

void DynamicAnimation::setCallback(std::function<void()>& callback) {
    this->callback = callback;
}

void DynamicAnimation::initialize (const std::vector<ui32>& frames, const uvec2& slices, const vec2& sliceSize) {
    const ui32 totalFrames = slices.x * slices.y;

    for (const ui32& frame : frames) {
        if (frame >= totalFrames) {
            std::cerr << "[Animation - Error] The frame given (" << frame << ") is ouside the bounds of the texture." << "\n";
        }

        sf::IntRect slice = calculateSliceDimensions(slices, sliceSize, frame);

        frameSlices.push_back(slice);
        frameSlicesMirrored.push_back(getMirroredSlice(slice));

        //ui32 xStart = frame % slices.x;
        //ui32 yStart = frame / slices.x;
        //
        //frameSlices.push_back(sf::IntRect(xStart * sliceSize.x, yStart * sliceSize.y, sliceSize.x, sliceSize.y));
        //frameSlicesMirrored.push_back(sf::IntRect((xStart + 1) * sliceSize.x, yStart * sliceSize.y, -sliceSize.x, sliceSize.y));
    }

    frameCount = frameSlices.size();
}

void DynamicAnimation::buildFrameTimeVector (const f32& frameTime) {
    for (size_t i = 0; i < frameTimes.size(); i++) {
        frameTimes[i] = frameTime;
    }
}
