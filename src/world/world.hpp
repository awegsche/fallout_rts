#ifndef __WORLD_H__
#define __WORLD_H__

#include "raylib.h"
#include "utils/cell_position.hpp"
#include "world/buildings.hpp"
#include "world/chunk.hpp"
#include "world/terrain.hpp"
#include <memory>
#include <optional>
#include <vector>

#include <iostream>

class World
{
  public:
    World(World const &)            = delete;
    World &operator=(World const &) = delete;

    World()
    {
        m_terrain_manager = std::make_unique<TerrainManager>();
        Shader shader     = LoadShader(R"(shaders\lighting_single_vs.glsl)", R"(shaders\lighting_fs.glsl)");
        shader.locs[SHADER_LOC_MATRIX_MVP]  = GetShaderLocation(shader, "mvp");
        shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
        // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader, "instanceTransform");

        // Set shader value: ambient light level
        int   ambientLoc = GetShaderLocation(shader, "ambient");
        float amb[4]     = { 0.2f, 0.2f, 0.2f, 1.0f };
        SetShaderValue(shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);

        UpdateLightValues(shader, 0);

        m_building_manager = std::make_unique<BuildingManager>(shader);

        std::random_device                    rd;
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        std::mt19937                          gen{ rd() };

        const size_t ncells = m_height * m_width * m_chunk_size * m_chunk_size;
        m_cells.reserve(ncells);
        m_cell_transforms.reserve(ncells);

        std::cout << "reserving space for " << ncells << "cells\n";
        std::cout << ncells * sizeof(Cell) / 1024 / 1024 << " MB of cell data\n";
        std::cout << ncells * sizeof(Matrix) / 1024 / 1024 << " MB of cell transform data\n";

        for (int j = 0; j < m_height; ++j) {
            for (int i = 0; i < m_width; ++i) {
                // m_chunks.emplace_back(m_chunk_size, i, j);
                Chunk ch{this, (uint32_t)i, (uint32_t)j};

                for (int h = 0; h < m_chunk_size; ++h) {
                    for (int w = 0; w < m_chunk_size; ++w) {
                        const float value = dist(gen) * 0.1f + 0.5f;
                        m_cells.emplace_back(TerrainType::Forest, value, -1);
                        const float x = ch.get_x_offset() + ((float)w + 0.2f + 0.6f * dist(gen)) * GROUND_TILE_SIZE;
                        const float y = ch.get_y_offset() + ((float)h + 0.2f + 0.6f * dist(gen)) * GROUND_TILE_SIZE;
                        Matrix      translation = MatrixTranslate(x, 0.0f, y);
                        Matrix      scale       = MatrixScale(1.0f + dist(gen) * 0.2f, dist(gen) * 0.3f + 1.0f, 1.0f);

                        m_cell_transforms.push_back(MatrixMultiply(scale, translation));
                    }
                }
            }
        }
    }

    void draw(Vector3 const &camera_pos) const
    {
        const auto pred = [this](Chunk const &chunk) {
            m_terrain_manager->draw_chunk(chunk);
            m_building_manager->draw(chunk);
        };
        do_for_visible_chunks(camera_pos, pred);
    }

    std::optional<CellPosition> click(Camera3D const &camera)
    {
        std::optional<CellPosition> pos = {};

        const auto pred = [&pos, &camera](Chunk const &chunk) {
            const auto _pos = chunk.get_mouse_over(camera);
            if (_pos) { pos = _pos; }
        };

        do_for_visible_chunks(camera.position, pred);
        return pos;
    }

    template<typename Pred> void do_for_visible_chunks(Vector3 const &camera_pos, Pred const &p) const
    {
        int x = camera_pos.x / m_chunk_size;
        int y = camera_pos.z / m_chunk_size;

        for (int j = y - 1; j <= y + 1; ++j) {
            for (int i = x - 1; i <= x + 1; ++i) {
                if (j >= 0 && j < m_height && i >= 0 && i < m_width) {
                    const Chunk chunk{this, (uint32_t)i, (uint32_t)j};
                    p(chunk);
                }
            }
        }
    }

    std::vector<Chunk>               m_chunks;
    std::unique_ptr<TerrainManager>  m_terrain_manager;
    std::unique_ptr<BuildingManager> m_building_manager;
    std::vector<Cell>                m_cells;
    std::vector<Matrix>              m_cell_transforms;
    std::vector<Building>            m_buildings;
    uint32_t                         m_chunk_size = 32;
    uint32_t                         m_width      = 10;
    uint32_t                         m_height     = 10;
};

#endif
