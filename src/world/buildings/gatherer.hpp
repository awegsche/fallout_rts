#ifndef __FOOD_GATHERER_H__
#define __FOOD_GATHERER_H__

#include "utils/cell_position.hpp"
#include "world/buildings/building.hpp"
#include <optional>
#include <string>
#include <utility>

constexpr float FOODGATHERER_TIME = 10.0f;

class World;

class Gatherer : public Building
{
    struct Instance
    {
        std::optional<CellPosition> connected_vault;
        uint8_t                     food     = 0;
        float                       progress = 0.0f;
    };

  public:
    Gatherer(std::string identifier, std::string source, std::string const &model, Renderer const &renderer)
        : Building(std::move(identifier)), m_source(std::move(source)), m_model(model.c_str(), renderer)
    {}

    ~Gatherer() = default;

    void update(World &world, float dt) override;

    void draw(Renderer &renderer) const override;

    void place(World &world, CellPosition position) override;

  private:
    std::vector<Instance> m_instances;
    std::string           m_source;
    InstancedModel        m_model;
};


#endif
