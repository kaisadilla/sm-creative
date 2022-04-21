#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "root.h"
#include "SpriteAnimation.h"

class DynamicAnimation : public SpriteAnimation {
private:
    i32 frameCount;
    i32 currentFrame = 0;
    f32 timeSinceLastFrame = 0.f;

    bool loop = true;
    std::vector<f32> frameTimes;
    std::vector<sf::IntRect> frameSlices;
    std::vector<sf::IntRect> frameSlicesMirrored;

    bool hasCallback = false;
    std::function<void()> callback = nullptr;

public:
    DynamicAnimation(const std::vector<f32>& frameTimes, const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize);
    DynamicAnimation(const f32 frameTime, const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize);
    DynamicAnimation(const f32 frameTime, const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize, std::function<void()> callback);
    DynamicAnimation(const DynamicAnimation& animation);
    ~DynamicAnimation();

    void onUpdate(const f32 deltaTime, const f32 speed) override;
    void reset() override;

    sf::IntRect getCurrentSlice(const bool mirrored) const override;

    void setLoop(const bool loop);
    void setCallback(std::function<void()>& callback);

private:
    void initialize(const std::vector<ui32>& frames, const uvec2& slices, const uvec2& sliceSize);
    void buildFrameTimeVector(const f32& frameTime);
};