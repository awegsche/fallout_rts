#ifndef __WORLD_H__
#define __WORLD_H__

#include "raylib.h"
#include "utils/cell_position.hpp"
#include "world/buildings/building.hpp"
#include "world/chunk.hpp"
#include "world/terrain.hpp"
#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include <iostream>

constexpr uint32_t DEFAULT_CHUNK_SIZE   = 64;
constexpr uint32_t DEFAULT_WORLD_WIDTH  = 10;
constexpr uint32_t DEFAULT_WORLD_HEIGHT = 10;

class Game;

class World
{
  public:
    World(World const &)            = delete;
    World &operator=(World const &) = delete;

    World();

    void draw(Game const &game) const;

    /* @brief Checks if the mouse is over something (e.g. when clicking on a tile). */
    [[nodiscard]] std::optional<CellPosition> click(Camera3D const &camera) const;

    /**
     * @brief Performs `pred` for each visible chunk (e.g. clicking or drawing functionality).
     *
     * @tparam Pred
     * @param camera_pos
     * @param pred A closure `void pred(Chunk const& chunk)`.
     */
    template<typename Pred> void do_for_visible_chunks(Vector3 const &camera_pos, Pred const &pred) const
    {
        int x = camera_pos.x / m_chunk_size;
        int y = camera_pos.z / m_chunk_size;

        for (int j = y - 1; j <= y + 1; ++j) {
            for (int i = x - 1; i <= x + 1; ++i) {
                if (j >= 0 && j < m_height && i >= 0 && i < m_width) {
                    const Chunk chunk{ this, (uint32_t)i, (uint32_t)j };
                    pred(chunk);
                }
            }
        }
    }

    /**
     * @brief Updates the game world, called once every frame.
     *
     * @param dt The time elpased since last frame.
     */
    void update(float dt) {
        for(auto& building: m_buildings) {
            building.second->update(*this, dt);
        }
    }

    std::vector<Chunk>               m_chunks;
    std::unique_ptr<TerrainManager>  m_terrain_manager;
    //std:
    //:unique_ptr<BuildingManager> m_building_manager;
    std::vector<Cell>                m_cells;
    std::vector<Matrix>              m_cell_transforms;
    //std::vector<Building>            m_buildings;
    std::unordered_map<std::string, Building*> m_buildings;
    uint32_t                         m_chunk_size = DEFAULT_CHUNK_SIZE;
    uint32_t                         m_width      = DEFAULT_WORLD_WIDTH;
    uint32_t                         m_height     = DEFAULT_WORLD_HEIGHT;
};

#endif
