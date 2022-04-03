
#include "..\..\header\game\Collider.h"

#include "game/Collider.h"

Collider::Collider () :
    center(vec2(0, 0)),
    distanceToEdge(vec2(0, 0)) 
{}

Collider::Collider(vec2 center, vec2 distanceToEdge) :
    center(center),
    distanceToEdge(distanceToEdge)
{}

bool Collider::checkColision(const Collider& collider) {
    // the distances of the centers of the two items.
    f32 xDelta = center.x - collider.center.x;
    f32 yDelta = center.y - collider.center.y;

    // checking if the sum of both colliders' distances to their respective edges
    // is higher than the distance between their centers.
    f32 xIntersect = abs(xDelta) - (distanceToEdge.x + collider.distanceToEdge.x);
    f32 yIntersect = abs(yDelta) - (distanceToEdge.y + collider.distanceToEdge.y);

    return xIntersect < 0.f && yIntersect < 0.f;
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
