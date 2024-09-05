#ifndef __VAULT_H__
#define __VAULT_H__

#include "raylib.h"
#include "utils/cell_position.hpp"
#include "world/buildings/building.hpp"
#include <string>

class Vault : public Building
{
  public:
    explicit Vault(std::string identifier, std::string const &model) : Building(std::move(identifier)), m_model(model) {}
    void update(World &world, float dt) override {}
    void draw() override
    {
        for (auto pos : m_positions) { m_model.draw(pos); }
    }

    void place(World &world, CellPosition position) override { m_positions.push_back(position); }

  private:
    SingleModelBuilding m_model;
};

#endif
