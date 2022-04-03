#include "world/Level.h"

Level::Level () :
    foregroundPlane(0, 0)
{}

Level::Level (const ui32& width, const ui32& height) :
    foregroundPlane(width, height)
{}
