#include "world/buildings.hpp"
#include "raylib.h"
#include "world/chunk.hpp"
#include "world/world.hpp"



void BuildingManager::place_building(BuildingKind kind, ChunkMut &chunk, int x, int y)
{
    chunk.get_cell_mut(x, y).object_idx = chunk.m_world->m_buildings.size();
    chunk.m_world_mut->m_buildings.push_back({ kind, { x, y } });
}
void BuildingManager::draw(Chunk const &chunk) const
{
    for (auto const &building : chunk.m_world->m_buildings) {
        auto model = m_models[(size_t)building.kind];
        model.transform = building.transform;
        DrawModel(model,
            { (float)building.position.x, 0.0f, (float)building.position.y },
            1.0f,
            { 255, 255, 255, 255 });
    }
}
