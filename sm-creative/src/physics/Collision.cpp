#include "physics/Collision.h"

Collision::Collision() :
    collider(nullptr),
    collision(false),
    direction(Direction::NONE),
    horizontalDirection(Direction::NONE),
    verticalDirection(Direction::NONE),
    intersection(vec2(0, 0))
{}

Collision::Collision (const Collider* collider, const bool collision, const Direction direction,
    const Direction horizontalDirection, const Direction verticalDirection,
    const vec2& intersection
) :
    collider(collider),
    collision(collision),
    direction(direction),
    horizontalDirection(horizontalDirection),
    verticalDirection(verticalDirection),
    intersection(intersection)
{}
