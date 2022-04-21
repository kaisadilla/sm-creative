#pragma once

#include "root.h"

enum class GameObjectType {
    Player = 0,
    Tile = 1,
    Enemy = 2,
    Item = 3
};

class IGameObject {
public:
    virtual GameObjectType getType() = 0;
};