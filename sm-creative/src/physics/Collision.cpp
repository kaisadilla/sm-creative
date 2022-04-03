#include "physics/Collision.h"

Collision::Collision() :
    collider(nullptr),
    direction(Direction::NONE),
    intersection(vec2(0, 0))
{}

Collision::Collision (const Collider* collider, Direction direction, vec2 intersection) :
    collider(collider),
    direction(direction),
    intersection(intersection)
{}
