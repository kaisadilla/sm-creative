#pragma once

#include "Tile.h"

class Block : public Tile {
private:
    bool isHidden = false;

public:
    Block(const bool isHidden);
};