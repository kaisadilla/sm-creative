#pragma once

#include "root.h"
#include "Collider.h"

class Collision {
    friend class Collider;

public:
    /// <summary>
    /// The collider this collider collided with.
    /// </summary>
    const Collider* collider;
    /// <summary>
    /// The side from which this collider collided with the other collider.
    /// </summary>
    Direction direction;
    // TODO: Speak English.
    /// <summary>
    /// The amount of distance, in each direction, that the others are inside each other.
    /// </summary>
    vec2 intersection;

public:
    Collision();
    Collision(const Collider* collider, Direction direction, vec2 intersection);
};