#pragma once

#include "root.h"

class Camera {
private:
    /// <summary>
    /// The width and height of the window, in pixels.
    /// </summary>
    uvec2 windowSize;
    /// <summary>
    /// Half the width and height of the window, in pixels.
    /// </summary>
    uvec2 windowHalves;
    vec2 viewMins;
    vec2 viewMaxes;

    sf::View view;

public:
    Camera();
    Camera(const uvec2 levelDimensions, const uvec2 windowDimensions);

    /// <summary>
    /// Updates the position of the camera according to the position of an object.
    /// </summary>
    /// <param name="target"></param>
    void updatePosition(vec2 target);

    inline sf::View& getView () {
        return view;
    }

    void __drawDebugLines(sf::RenderWindow& window);
};