#include "world.hpp"

#include "game.hpp"

void World::draw(Game const &game) const
{
    const auto pred = [this, &game](Chunk const &chunk) {
        m_terrain_manager->draw_chunk(chunk);
        m_building_manager->draw(chunk, game);
    };
    do_for_visible_chunks(game.camera.target, pred);
}

