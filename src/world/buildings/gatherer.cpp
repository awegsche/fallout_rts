#include "gatherer.hpp"
#include <spdlog/spdlog.h>

#include "utils/cell_position.hpp"
#include "world/world.hpp"

void Gatherer::update(World &world, float dt)
{
    for (auto &inst : m_instances) {
        if (!inst.connected_vault.has_value()) { continue; }
        inst.progress += dt;
        if (inst.progress > FOODGATHERER_TIME) {
            ++inst.food;
            inst.progress -= FOODGATHERER_TIME;
        }
    }
}

void Gatherer::place(World &world, CellPosition position)
{
    Instance inst;

    auto const b = world.m_buildings.at(m_source);
    spdlog::debug("place gatherer");

    for (CellPosition const &pos : b->m_positions) {
        if (position.dist_squared(pos) < 100) {
            spdlog::debug("found Vault in vicinity");
            inst.connected_vault = pos;
            break;
        }
    }

    if (!inst.connected_vault) { spdlog::debug("no vault nearby"); }

    m_instances.push_back(inst);
    m_positions.push_back(position);
}

void Gatherer::draw()
{
    for (auto pos : m_positions) { m_model.draw(pos); }
};
