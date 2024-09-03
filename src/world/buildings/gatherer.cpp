#include "gatherer.hpp"
#include <iostream>

#include "utils/cell_position.hpp"
#include "world/world.hpp"

void Gatherer::update(World &world, float dt)
{
    for (auto& inst : m_instances) {
        if (!inst.connected_vault.has_value()) { continue; }
        inst.progress += dt;
        if (inst.progress > FOODGATHERER_TIME) {
            ++inst.food;
            inst.progress -= FOODGATHERER_TIME;
            std::cout << "food: " << (int)inst.food << "\n";
        }
    }
}

void Gatherer::place(World &world, CellPosition position)
{
    Instance inst;

    auto const *b = world.m_buildings.at(m_source);
    std::cout << "place gatherer\n";

    for (CellPosition const &pos : b->m_positions) {
        if (position.dist_squared(pos) < 100) {
            std::cout << "found Vault in vicinity\n";
            inst.connected_vault = pos;
            break;
        }
    }

    m_instances.push_back(inst);
    m_positions.push_back(position);
}

void Gatherer::draw()
{
    for (auto pos : m_positions) {
        m_model.draw(pos);
    }
};
