#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "world/buildings.hpp"
#include "world/chunk.hpp"
#include <cstdint>

class Player
{
  public:
    uint32_t population;


    void count_population(std::vector<Chunk> const &chunks)
    {
        population = 0;
        for (const auto &chunk : chunks) {
            for (const auto &building : chunk.buildings) {
                switch (building.kind) {
                case BuildingKind::Shack01:
                    population += building.value;
                    break;
                default:
                    break;
                }
            }
        }
    }
};

#endif
