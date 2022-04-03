#pragma once

#include "root.h"
#include "Collision.h"

class Collision;

class Collider {
private:
    vec2 center;
    vec2 distanceToEdge;

public:
    Collider();
    Collider(vec2 center, vec2 distanceToEdge);

    bool checkColision(const Collider& collider, Collision& collision);
    sf::FloatRect getBounds() const;

    void drawColliderBounds(sf::RenderWindow& window) const;

    inline void setCenter (const vec2& center) {
        this->center = center;
    }

    inline void setDistanceToEdge (const vec2& distanceToEdge) {
        this->distanceToEdge = distanceToEdge;
    }
};