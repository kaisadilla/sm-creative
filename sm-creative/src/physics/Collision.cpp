#include "physics/Collision.h"

Collision::Collision() :
    collider(nullptr),
    collision(false),
    direction(Direction::NONE),
    intersection(vec2(0, 0))
{}

Collision::Collision (const Collider* collider, const bool collision, const Direction direction, const vec2& intersection) :
    collider(collider),
    collision(collision),
    direction(direction),
    intersection(intersection)
{}
