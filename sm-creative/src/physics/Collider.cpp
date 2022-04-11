#include "physics/Collider.h"

Collider::Collider () :
    gameObject(nullptr),
    center(vec2(0, 0)),
    distanceToEdge(vec2(0, 0)) 
{}

Collider::Collider(IGameObject * gameObject) :
    gameObject(gameObject),
    center(vec2(0, 0)),
    distanceToEdge(vec2(0, 0))
{}

Collider::Collider(IGameObject* gameObject, vec2 center, vec2 distanceToEdge) :
    gameObject(gameObject),
    center(center),
    distanceToEdge(distanceToEdge)
{}

void Collider::calculateVectorsInsideSprite (const vec2& spriteSize, const sf::IntRect& colliderPosition, vec2& center, vec2& distanceToEdge) {
    // the offsets of the collider's top-left corner in relation to the sprite's top-left corner.
    const i32& xOffset = colliderPosition.left;
    const i32& yOffset = colliderPosition.top;

    // the center of the collider relative to itself, which is also the distance to the edge.
    f32 xHalf = colliderPosition.width / 2.f;
    f32 yHalf = colliderPosition.height / 2.f;

    // adding the top-left offset to the center returns the position of the center relative to the sprite.
    center = vec2(xHalf + xOffset, yHalf + yOffset);
    distanceToEdge = vec2(xHalf, yHalf);
}

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

void Collider::drawColliderBounds (sf::RenderWindow& window, const sf::Color& color) const {
    constexpr f32 OFFSET = 0.1f;

    sf::Vertex lines[5];
    lines[0].position = center - distanceToEdge + vec2(OFFSET, OFFSET);
    lines[0].color = color;
    lines[1].position = vec2(center.x - distanceToEdge.x + OFFSET, center.y + distanceToEdge.y);
    lines[1].color = color;
    lines[2].position = center + distanceToEdge;
    lines[2].color = color;
    lines[3].position = vec2(center.x + distanceToEdge.x, center.y - distanceToEdge.y + OFFSET);
    lines[3].color = color;
    lines[4].position = center - distanceToEdge + vec2(OFFSET, OFFSET);
    lines[4].color = color;
    window.draw(lines, 5, sf::LineStrip);
}
