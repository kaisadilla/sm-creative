#pragma once

#include "root.h"
#include "Collision.h"
#include "IGameObject.h"

class Collision;

class Collider {
private:
    IGameObject* gameObject;
    vec2 center;
    vec2 distanceToEdge;

public:
    Collider();
    Collider(IGameObject* gameObject, vec2 center, vec2 distanceToEdge);

    bool checkColision(const Collider& collider, Collision& collision);
    sf::FloatRect getBounds() const;

    void drawColliderBounds(sf::RenderWindow& window, const sf::Color& color) const;

    inline IGameObject* getGameObject () const {
        return gameObject;
    }

    inline void setCenter (const vec2& center) {
        this->center = center;
    }

    inline void setDistanceToEdge (const vec2& distanceToEdge) {
        this->distanceToEdge = distanceToEdge;
    }
};