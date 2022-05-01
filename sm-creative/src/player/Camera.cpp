
#include "..\..\header\player\Camera.h"

#include "player/Camera.h"

Camera::Camera () {}

//Camera::Camera (const uvec2 levelDimensions, const uvec2 windowDimensions) :
//    levelWidth(levelDimensions.x),
//    levelHeight(levelDimensions.y),
//    windowWidth(windowDimensions.x),
//    windowHeight(windowDimensions.y),
//    windowHalfWidth(windowDimensions.x / 2),
//    windowHalfHeight(windowDimensions.y / 2),
//    view(sf::FloatRect(0, 0, windowWidth, windowHeight))
//{
//
//}

Camera::Camera (const uvec2 levelDimensions, const uvec2 windowDimensions) :
    windowSize(windowDimensions),
    windowHalves(vec2(windowSize.x / 2, windowSize.y / 2)),
    view(sf::FloatRect(0, 0, windowSize.x, windowSize.y))
{
    ui32 xMin = windowHalves.x;
    ui32 yMin = windowHalves.y;

    ui32 xMax = levelDimensions.x - windowHalves.x;
    ui32 yMax = levelDimensions.y - windowHalves.y;

    // for y, if the min is higher than the max, it becomes the max.
    // This means that we'll always show more sky instead of more underground.
    yMin = std::min(yMin, yMax);
    // for x, if the max is lower than the min, it becomes the min.
    // This means that we'll always show leftover space to the right instead of the left.
    xMax = std::max(xMin, xMax);

    viewMins = vec2(xMin, yMin);
    viewMaxes = vec2(xMax, yMax);
}

void Camera::updatePosition (vec2 target) {
    // TODO: Make this parameter configurable. This is half of the total size of the player entity.
    constexpr f32 __TEMPORARY_MARIO_HARDCODED_OFFSET = 16.f;

    f32 x = std::clamp(target.x + __TEMPORARY_MARIO_HARDCODED_OFFSET, viewMins.x, viewMaxes.x);
    f32 y = std::clamp(target.y + __TEMPORARY_MARIO_HARDCODED_OFFSET, viewMins.y, viewMaxes.y);

    f32 xFixed = ((int)(x * 10.f) / 10.f) + 0.01f;
    f32 yFixed = ((int)(y * 10.f) / 10.f) + 0.01f;

    view.setCenter(vec2(xFixed, yFixed));
    //topLeftPoint = vec2((int)(target.x - windowHalfWidth), (int)(target.y - windowHalfHeight));
}

void Camera::__drawDebugLines (sf::RenderWindow& window) {
    sf::RectangleShape relativeCenter(vec2(6.f, 6.f));
    relativeCenter.setFillColor(sf::Color::Green);
    relativeCenter.setPosition((vec2)windowHalves);
    window.draw(relativeCenter);

    //sf::Vertex line[2];
    //line[0].position = sf::Vector2f(10, 0);
    //line[0].color = sf::Color::Red;
    //line[1].position = sf::Vector2f(20, 0);
    //line[1].color = sf::Color::Red;
}
