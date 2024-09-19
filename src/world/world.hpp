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
    World();

    World(World const &)            = delete;
    World &operator=(World const &) = delete;

    ~World() = default;

    void draw(Game &game);

    /* @brief Checks if the mouse is over something (e.g. when clicking on a tile). */
    [[nodiscard]] std::optional<CellPosition> click(Camera3D const &camera) const;

    /**
     * @brief Updates the game world, called once every frame.
     *
     * @param dt The time elpased since last frame.
     */
    void update(float dt);

    void place_building(const std::string identifier, CellPosition position);

    Cell &get_cell_mut(CellPosition position) { return m_cells[position.x + position.y * m_chunk_size * m_width]; }

    /**
     * @brief Performs `pred` for each visible chunk (e.g. clicking or drawing functionality).
     *
     * @tparam Pred
     * @param camera_pos
     * @param pred A closure `void pred(Chunk const& chunk)`.
     */
    template<typename Pred> void do_for_visible_chunks(Vector3 const &camera_pos, Pred const &pred) const
    {
        int x = (int)camera_pos.x / (int)m_chunk_size;
        int y = (int)camera_pos.z / (int)m_chunk_size;

        for (int j = y - 1; j <= y + 1; ++j) {
            for (int i = x - 1; i <= x + 1; ++i) {
                if (j >= 0 && j < m_height && i >= 0 && i < m_width) {
                    const Chunk chunk{ this, (uint32_t)i, (uint32_t)j };
                    pred(chunk);
                }
            }
        }
    }

    template<class T, class... Args> void new_building_type(Args &&...args)
    {
        auto new_building                       = std::make_shared<T>(args...);
        m_buildings[new_building->identifier()] = new_building;
    }

  public:// todo: make private and add accessors
    std::vector<Chunk>              m_chunks;
    std::unique_ptr<TerrainManager> m_terrain_manager;
    // std:
    //: unique_ptr<BuildingManager> m_building_manager;
    std::vector<Cell>   m_cells;
    std::vector<Matrix> m_cell_transforms;

    std::unordered_map<std::string, std::shared_ptr<Building>> m_buildings; // maybe just a vec?

    uint32_t m_chunk_size = DEFAULT_CHUNK_SIZE;
    uint32_t m_width      = DEFAULT_WORLD_WIDTH;
    uint32_t m_height     = DEFAULT_WORLD_HEIGHT;
};

#endif
