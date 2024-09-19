#ifndef __VAULT_H__
#define __VAULT_H__

#include "utils/cell_position.hpp"
#include "world/buildings/building.hpp"
#include <string>

class Vault : public Building
{
  public:
    explicit Vault(std::string identifier, std::string const &model, Renderer const& renderer) : Building(std::move(identifier)), m_model(model, renderer) {}
    void update(World &world, float dt) override {}
    void draw(Renderer &renderer) const override
    {
        renderer.reset_instances();
        for (auto pos : m_positions) {
            renderer.push_instance_transform(pos.to_translation_matrix()); }

        renderer.draw_instances(m_model);
    }

    void place(World &world, CellPosition position) override { m_positions.push_back(position); }

  private:
    InstancedModel m_model;
};

#endif
