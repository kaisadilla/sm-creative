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
    Collider(IGameObject* gameObject);
    Collider(IGameObject* gameObject, vec2 center, vec2 distanceToEdge);

    /// <summary>
    /// Calculates the center and distance to the edge of a collider relative to a sprite,
    /// given the dimensions of the sprite and a rectangle that represents the position of
    /// the collider inside it.
    /// </summary>
    /// <param name="spriteSize">The dimensions of the sprite.</param>
    /// <param name="colliderPosition">A rectangle representing the collider inside the sprite,
    /// with the (x, y) coordinates of the top left corner and the width and height of the collider.</param>
    /// <param name="center">Returns the center obtained by the calculation.</param>
    /// <param name="distanceToEdge">Returns the distance to the edge obtained by the calculation.</param>
    static void calculateVectorsInsideSprite(const vec2& spriteSize, const sf::IntRect& colliderPosition, vec2& center, vec2& distanceToEdge);

    bool checkColision(const Collider& collider, Collision& collision);
    sf::FloatRect getBounds() const;

    void drawColliderBounds(sf::RenderWindow& window, const sf::Color& color) const;


public:
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