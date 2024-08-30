#include "terrain.hpp"
#include "world/chunk.hpp"
#include <cstdio>


void TerrainManager::draw_chunk(Chunk const &chunk)
{
    tree01_model.transforms.clear();
    tree02_model.transforms.clear();

    rlBegin(RL_TRIANGLES);
    for (size_t i = 0; i < chunk.chunk_size(); ++i) {
        for (size_t j = 0; j < chunk.chunk_size(); ++j) {
            const Cell &cell = chunk.get_cell(i, j);

            const uint8_t clr = static_cast<uint8_t>(cell.terrain_value * 255.0f * 0.5f);
            const float   x   = chunk.get_x_offset() + static_cast<float>(i) * GROUND_TILE_SIZE;
            const float   y   = chunk.get_y_offset() + static_cast<float>(j) * GROUND_TILE_SIZE;

            rlColor4ub(127 + clr, 64 + clr, clr, 255);
            rlVertex3f(x, 0.0f, y);
            rlVertex3f(x, 0.0f, y + GROUND_TILE_SIZE);
            rlVertex3f(x + GROUND_TILE_SIZE, 0.0f, y);

            rlVertex3f(x, 0.0f, y + GROUND_TILE_SIZE);
            rlVertex3f(x + GROUND_TILE_SIZE, 0.0f, y + GROUND_TILE_SIZE);
            rlVertex3f(x + GROUND_TILE_SIZE, 0.0f, y);

            if (cell.object_idx == -1) {
                switch (cell.terrain_type) {
                case TerrainType::Forest:
                    tree01_model.transforms.push_back(chunk.get_cell_transform(i, j));
                    break;
                }
            }
        }
    }
    rlEnd();

    // printf("rendering %d trees", tree01_model.transforms.size());
    DrawMeshInstanced(tree01_model.model.meshes[0],
        tree01_model.model.materials[0],
        tree01_model.transforms.data(),
        tree01_model.transforms.size());
}
