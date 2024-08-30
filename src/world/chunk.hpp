#ifndef __CHUNK_H__
#define __CHUNK_H__

#include <cstdint>
#include <random>

#include "utils/cell_position.hpp"
#include "world/buildings.hpp"
#include "world/terrain.hpp"
#include <raylib.h>
#include <raymath.h>


class World;

struct Cell
{
    // ground / nature info
    TerrainType terrain_type  = TerrainType::Plain;
    float       terrain_value = 0.0f;

    // is something built on top?
    int32_t object_idx = -1;
};


struct Chunk
{
    Chunk(World const *world, uint32_t x, uint32_t y) : m_world(world), pos_x(x), pos_y(y) {}

    [[nodiscard]] Cell const &get_cell(int i, int j) const;
    [[nodiscard]] Matrix const &get_cell_transform(int i, int j) const;


    void tick(Camera3D const &cam) {}

    [[nodiscard]] float get_x_offset() const;
    [[nodiscard]] float get_y_offset() const;

    [[nodiscard]] bool mouse_is_over() const { return m_mouse_collision.hit; }

    [[nodiscard]] uint32_t chunk_size() const;

    [[nodiscard]] size_t get_cell_position(int i, int j) const;

    /** Returns the position of the cell the mouse is over.
     *
     * The return value of this function is only meaningfull if `mouse_is_over()` returns `true`.
     *
     **/
    [[nodiscard]] std::optional<CellPosition> get_mouse_over(Camera3D const &cam) const;

    uint32_t     pos_x;
    uint32_t     pos_y;
    World const *m_world;


    RayCollision m_mouse_collision;
};

struct ChunkMut: public Chunk {
    ChunkMut(World* world, uint32_t x, uint32_t y):
        Chunk(const_cast<World const*>(world), x, y), m_world_mut(world) {}

    [[nodiscard]] Cell &get_cell_mut(int i, int j);

    World* m_world_mut;
};

#endif
