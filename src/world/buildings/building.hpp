#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "utils/cell_position.hpp"
#include "utils/renderer.hpp"
#include "world/chunk.hpp"
#include "world/terrain.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

class World;

enum class BuildingSurvivalKind { Alive, Dead, Remove };

class Building
{
  public:
    Building(std::string identifier) : m_identifier(std::move(identifier)) {}

    virtual ~Building() = default;

    virtual void update(World &world, float dt)             = 0;
    virtual void draw(Renderer &renderer) const             = 0;
    virtual void place(World &world, CellPosition position) = 0;

    [[nodiscard]] std::string const &identifier() const { return m_identifier; }

    std::vector<CellPosition> m_positions;

  protected:
    std::string m_identifier;
};

class SingleModelBuilding
{
  public:
    explicit SingleModelBuilding(std::string const &model_path) { m_model = LoadModel(model_path.c_str()); }

    ~SingleModelBuilding() { UnloadModel(m_model); }

    void draw(CellPosition position) const { DrawModel(m_model, position.to_vector3(), 1.0f, WHITE); }

    void draw_single(CellPosition position) const { draw(position); }

  private:
    Model m_model{};
};


#endif
