#pragma once

#include "root.h"

class SpriteAnimation {
public:
    virtual void onUpdate(const f32 deltaTime, const f32 speed) = 0;
    virtual void reset() = 0;

    virtual sf::IntRect getCurrentSlice(const bool mirrored) const = 0;

protected:
    /// <summary>
    /// Given information about the spritesheet and the position of the slice inside the spritesheet,
    /// returns the coordinates of the slice.
    /// </summary>
    /// <param name="index">The index of the slice, left to right and then top to bottom.</param>
    /// <param name="slices">The dimensions of the spritesheet, in sprites.</param>
    /// <param name="sliceSize">The size of each sprite, in pixels.</param>
    sf::IntRect calculateSliceDimensions(const uvec2& slices, const uvec2& sliceSize, const ui32 index);

    /// <summary>
    /// Returns the coordinates of the same slice given, but mirrored (flipped horizontally).
    /// </summary>
    /// <param name="slice">The original coordinates of the slice.</param>
    /// <returns></returns>
    sf::IntRect getMirroredSlice(const sf::IntRect& slice);
};