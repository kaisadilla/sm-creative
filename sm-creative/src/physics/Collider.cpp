#include "physics/Collider.h"

Collider::Collider () :
    gameObject(nullptr),
    center(vec2(0, 0)),
    distanceToEdge(vec2(0, 0)) 
{}

Collider::Collider(IGameObject* gameObject, vec2 center, vec2 distanceToEdge) :
    gameObject(gameObject),
    center(center),
    distanceToEdge(distanceToEdge)
{}

bool Collider::checkColision(const Collider& collider, Collision& collision) {
    // the distances of the centers of the two items.
    f32 xDelta = center.x - collider.center.x;
    f32 yDelta = center.y - collider.center.y;

    // checking if the sum of both colliders' distances to their respective edges
    // is higher than the distance between their centers.
    f32 xIntersect = abs(xDelta) - (distanceToEdge.x + collider.distanceToEdge.x);
    f32 yIntersect = abs(yDelta) - (distanceToEdge.y + collider.distanceToEdge.y);

    bool wasCollision = xIntersect < 0.f && yIntersect < 0.f;
    Direction direction = Direction::NONE;

    if (wasCollision) {
        if (xIntersect > yIntersect) {
            direction = xDelta > 0.f ? Direction::LEFT : Direction::RIGHT;
        }
        else {
            direction = yDelta > 0.f ? Direction::UP : Direction::DOWN;
        }
    }

    // Remember that, when a collision occurs, x and y intersect will always be negative, so -xIntersect results in a positive number.
    f32 xIntersectSigned = xDelta > 0.f ? -xIntersect : xIntersect;
    f32 yIntersectSigned = yDelta > 0.f ? -yIntersect : yIntersect;

    collision = Collision(&collider, wasCollision, direction, vec2(xIntersectSigned, yIntersectSigned));

    return xIntersect < 0.f && yIntersect < 0.f;
}

sf::FloatRect Collider::getBounds () const {
    return sf::FloatRect(center - distanceToEdge, distanceToEdge * 2.f);
}

void Collider::drawColliderBounds (sf::RenderWindow& window) const {
    sf::Vertex lines[5];
    lines[0].position = center - distanceToEdge;
    lines[0].color = sf::Color::Green;
    lines[1].position = vec2(center.x - distanceToEdge.x, center.y + distanceToEdge.y);
    lines[1].color = sf::Color::Green;
    lines[2].position = center + distanceToEdge;
    lines[2].color = sf::Color::Green;
    lines[3].position = vec2(center.x + distanceToEdge.x, center.y - distanceToEdge.y);
    lines[3].color = sf::Color::Green;
    lines[4].position = center - distanceToEdge;
    lines[4].color = sf::Color::Green;
    window.draw(lines, 5, sf::LineStrip);
}
