#pragma once

#include "root.h"
#include "SpriteAnimation.h"

class StaticAnimation : public SpriteAnimation {
    sf::IntRect frameSlice;
    sf::IntRect frameSliceMirrored;

public:
    StaticAnimation(const uvec2& slices, const vec2& sliceSize, const ui32 frame);
    StaticAnimation(const StaticAnimation& animation);

    void onUpdate(const f32 deltaTime, const f32 speed) override {};
    void reset() override {};

    sf::IntRect getCurrentSlice(const bool mirrored) const override;
};