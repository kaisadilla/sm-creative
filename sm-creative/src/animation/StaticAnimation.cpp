#include "animation/StaticAnimation.h"

StaticAnimation::StaticAnimation (const uvec2& slices, const uvec2& sliceSize, const ui32 frame) :
    frameSlice(calculateSliceDimensions(slices, sliceSize, frame)),
    frameSliceMirrored(getMirroredSlice(frameSlice))
{}

StaticAnimation::StaticAnimation(const StaticAnimation & animation) :
    frameSlice(animation.frameSlice),
    frameSliceMirrored(animation.frameSliceMirrored)
{}

sf::IntRect StaticAnimation::getCurrentSlice(const bool mirrored) const {
    return mirrored ? frameSliceMirrored : frameSlice;
}
