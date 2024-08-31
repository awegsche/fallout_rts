#include "world/buildings.hpp"
#include "raylib.h"
#include "utils/cell_position.hpp"
#include "world/chunk.hpp"
#include "world/world.hpp"

#include "game.hpp"

void BuildingManager::place_building(BuildingKind kind, ChunkMut &chunk, int x, int y)
{
    chunk.get_cell_mut(x, y).object_idx = chunk.m_world->m_buildings.size();
    chunk.m_world_mut->m_buildings.push_back({ kind, { x, y } });
}

void BuildingManager::draw(Chunk const &chunk, Game const& game) const
{
    if (game.state == GameState::Building && chunk.contains_position(game.mouse_over.value())) {
        CellPosition mouse_over = game.mouse_over.value();
        auto model = m_models[(size_t)game.buildin_kind];
        DrawModel(model, {(float)mouse_over.x, 0.0f, (float)mouse_over.y}, 1.0f, {255,255,255,255});
    }
    for (auto const &building : chunk.m_world->m_buildings) {
        if (building.survival_kind == BuildingSurvivalKind::Alive && !chunk.contains_position(building.position)) {
            continue;
        }
        auto model      = m_models[(size_t)building.kind];
        model.transform = building.transform;
        DrawModel(
            model, { (float)building.position.x, 0.0f, (float)building.position.y }, 1.0f, { 255, 255, 255, 255 });
    }
}
