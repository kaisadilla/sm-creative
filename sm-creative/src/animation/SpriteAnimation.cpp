#include "animation/SpriteAnimation.h"

SpriteAnimation::~SpriteAnimation () {
    std::cout << "Destroyed sprite animation. \n";
}

sf::IntRect SpriteAnimation::calculateSliceDimensions (const uvec2& slices, const vec2& sliceSize, const ui32 index) {
    ui32 xStart = index % slices.x;
    ui32 yStart = index / slices.x;

    return sf::IntRect(xStart * sliceSize.x, yStart * sliceSize.y, sliceSize.x, sliceSize.y);
}

sf::IntRect SpriteAnimation::getMirroredSlice (const sf::IntRect& slice) {
    return sf::IntRect(slice.left + slice.width, slice.top, -slice.width, slice.height);
}
