#include "animation/SpriteAnimation.h"

sf::IntRect SpriteAnimation::calculateSliceDimensions (const uvec2& slices, const uvec2& sliceSize, const ui32 index) {
    ui32 xStart = index % slices.x;
    ui32 yStart = index / slices.x;

    return sf::IntRect(xStart * sliceSize.x, yStart * sliceSize.y, sliceSize.x, sliceSize.y);
}

sf::IntRect SpriteAnimation::getMirroredSlice (const sf::IntRect& slice) {
    return sf::IntRect(slice.left + slice.width, slice.top, -slice.width, slice.height);
}
