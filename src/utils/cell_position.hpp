#ifndef __CELL_POSITION_H__
#define __CELL_POSITION_H__

#include "raylib.h"
#include "world/terrain.hpp"
struct CellPosition
{
    int x;
    int y;

    CellPosition operator-(CellPosition other) const { return { x - other.x, y - other.y }; }

    [[nodiscard]] int length_squared() const { return x * x + y * y; }

    [[nodiscard]] int dist_squared(CellPosition other) const { return (other - *this).length_squared(); }

    [[nodiscard]] Vector3 to_vector3(float height = 0.0f) const
    {
        return { x * GROUND_TILE_SIZE, height, y * GROUND_TILE_SIZE };
    }

    [[nodiscard]] Matrix to_translation_matrix(float height = 0.0f) const {
        return {
            1.0f, 0.0f, 0.0f, static_cast<float>(x) * GROUND_TILE_SIZE,
            0.0f, 1.0f, 0.0f, height,
            0.0f, 0.0f, 1.0f, static_cast<float>(y) * GROUND_TILE_SIZE,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
};


#endif
