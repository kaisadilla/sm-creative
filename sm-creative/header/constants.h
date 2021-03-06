#pragma once

#include "root.h"

// resolution: 16:9.
//constexpr ui32 WINDOW_WIDTH_IN_TILES = 32;
//constexpr ui32 WINDOW_HEIGHT_IN_TILES = 18;
constexpr ui32 WINDOW_WIDTH_IN_TILES = 24;
constexpr ui32 WINDOW_HEIGHT_IN_TILES = 14;

constexpr ui32 PIXELS_PER_TILE = 16;

constexpr f32 SECONDS_PER_FIXED_UPDATE = 0.01f;

constexpr f32 DEAD_ENEMY_DESPAWN_TIME = 0.25f;