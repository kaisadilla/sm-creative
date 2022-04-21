#pragma once

#include "root.h"
#include "entities/Mob.h"

/// <summary>
/// WARNING: Requires SceneLevel.h to be imported in the child class, too.
/// </summary>
class IAvoidCliffs {
protected:
    bool avoidsCliffs;
    i32 offsetDown;
    ivec2 checkedCliffTile = ivec2(-2, 0);

    sf::RectangleShape debug_checkedCliffTile;

protected:
    IAvoidCliffs(const bool avoidsCliffs, const f32 mobHeight);

    void onStart();
    void checkCliffs(Mob* mob, f32 speed);
    void drawDebugInfo_cliffDetection(sf::RenderWindow& window);
};