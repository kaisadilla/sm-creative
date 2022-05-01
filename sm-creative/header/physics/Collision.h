#pragma once

#include "root.h"
#include "Collider.h"

class IGameObject;

class Collision {
    friend class Collider;

public:
    /// <summary>
    /// The collider this collider collided with.
    /// </summary>
    const Collider* collider;
    /// <summary>
    /// True if there was a collision.
    /// </summary>
    bool collision;
    /// <summary>
    /// The side of this collider that collided with the other agent
    /// (whichever is greatest between horizontal and vertical directions).
    /// </summary>
    Direction direction;
    /// <summary>
    /// The horizontal side of this collider that collided with the other agent.
    /// </summary>
    Direction horizontalDirection;
    /// <summary>
    /// The vertical side of this collider that collided with the other agent.
    /// </summary>
    Direction verticalDirection;
    /// <summary>
    /// A vector representing the overlap between the two colliders.
    /// </summary>
    vec2 intersection;

public:
    Collision();
    Collision(const Collider* collider, const bool collision, const Direction direction,
        const Direction horizontalDirection, const Direction verticalDirection,
        const vec2& intersection
    );

    /// <summary>
    /// Returns the side of the game object given that was hit by this collision .
    /// </summary>
    /// <param name="gameObject">The game object to check.</param>
    inline Direction getDirectionForGameObject (const IGameObject* gameObject) const {
        return gameObject == collider->getGameObject() ? direction : getOppositeDirection(direction);
    }

    /// <summary>
    /// Returns the horizontal side of the game object given that was hit by this collision .
    /// </summary>
    /// <param name="gameObject">The game object to check.</param>
    inline Direction getHorizontalDirectionForGameObject (const IGameObject* gameObject) const  {
        return gameObject == collider->getGameObject() ? horizontalDirection : getOppositeDirection(horizontalDirection);
    }

    /// <summary>
    /// Returns the vertical side of the game object given that was hit by this collision .
    /// </summary>
    /// <param name="gameObject">The game object to check.</param>
    inline Direction getVerticalDirectionForGameObject (const IGameObject* gameObject) const {
        return gameObject == collider->getGameObject() ? verticalDirection : getOppositeDirection(verticalDirection);
    }
};