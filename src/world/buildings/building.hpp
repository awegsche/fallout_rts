#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "utils/cell_position.hpp"
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
    virtual void update(World &world, float dt) = 0;
    virtual void draw()                         = 0;
    virtual void place(World &world, CellPosition position) = 0;

    std::vector<CellPosition> m_positions;
  //protected:
    ~Building() = default;
};

class SingleModelBuilding {
    public:
        SingleModelBuilding(std::string const& model_path) {
            m_model = LoadModel(model_path.c_str());
        }

        ~SingleModelBuilding() {
            UnloadModel(m_model);
        }

        void draw(CellPosition position) const {
            DrawModel(m_model, position.to_vector3(), 1.0f, WHITE);
        }

    private:
    Model m_model{};
};


#endif
