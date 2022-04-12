#pragma once

#include <SFML/Graphics.hpp>

typedef sf::Vector2f vec2;
typedef sf::Vector2i ivec2;
typedef sf::Vector2u uvec2;

template<typename T>
class Grid2 {
private:
    ui32 width;
    ui32 height;

    std::vector<T> grid;

public:
    Grid2 (const ui32 width, const ui32 height) :
        width(width),
        height(height),
        grid(width * height)
    {}

    Grid2 (const Grid2<T>& original) :
        width(original.width),
        height(original.height),
        grid(original.grid)
    {}
    
    inline ui32 getWidth () const {
        return width;
    }

    inline ui32 getHeight () const {
        return height;
    }

    inline T& getAt (const ui32 x, const ui32 y) {
        return grid[getIndex(x, y)];
    }

    inline void setAt (const ui32 x, const ui32 y, const T& item) {
        grid[getIndex(x, y)] = item;
    }

private:
    inline ui32 getIndex (const ui32 x, const ui32 y) {
        return (y * width) + x;
    }
};

enum class Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = 4
};

inline Direction getOppositeDirection (Direction direction) {
    if (direction == Direction::UP)         return Direction::DOWN;
    else if (direction == Direction::DOWN)  return Direction::UP;
    else if (direction == Direction::LEFT)  return Direction::RIGHT;
    else if (direction == Direction::RIGHT) return Direction::LEFT;
    else return Direction::NONE;
}

// TODO: Move somewhere else, anyway we probably won't use this.
inline f32 roundDownToNearest (f32 number, f32 target) {
    return std::floorf(number / target) * target;
}