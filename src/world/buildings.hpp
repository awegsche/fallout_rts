#ifndef __BUILDING_MANAGER_H__
#define __BUILDING_MANAGER_H__

#include "utils/cell_position.hpp"
#include <array>
#include <raylib.h>
#include <raymath.h>

enum class BuildingKind: uint32_t {
    Vault,
    Shack01,
    StreetStraight,
    StreetTwo,
    StreetThree,
    BuildingCount
};

class Chunk;
class ChunkMut;

class BuildingManager {
    public:
        explicit BuildingManager(Shader shader) {
            m_models[(size_t)BuildingKind::Vault] = LoadModel("assets\\vault.obj");
            m_models[(size_t)BuildingKind::Shack01] = LoadModel("assets\\shack01.obj");
            m_models[(size_t)BuildingKind::StreetStraight] = LoadModel("assets\\street_colorful.obj");
            m_models[(size_t)BuildingKind::StreetTwo] = LoadModel("assets\\street_two.obj");
            m_models[(size_t)BuildingKind::StreetThree] = LoadModel("assets\\street_three.obj");

            for (const auto& model: m_models) {
                model.materials[0].shader = shader;
            }
        }

        static void place_building(BuildingKind kind, ChunkMut& chunk, int x, int y);

        void draw(Chunk const& chunk) const;

    private:
        std::array<Model, (size_t)BuildingKind::BuildingCount> m_models{};
};

struct BuildingBase {

};

struct Building {
    BuildingKind kind;
    CellPosition position;
    int value;
    Matrix transform = MatrixIdentity();
};

#endif
