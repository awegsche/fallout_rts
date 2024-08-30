#ifndef __WORLDSTATE_H__
#define __WORLDSTATE_H__

#include <string>

#include <raylib.h>

#include "world/terrain.hpp"

struct WorldState
{
    WorldState(Shader shader)
    {
        terrains.reserve(terrains_width * terrains_height);

        for (int j = 0; j < terrains_height; ++j) {
            for (int i = 0; i < terrains_width; ++i) {
                terrains.emplace_back(terrain_width, terrain_height, i, j, shader);
            }
        }
    }

    Camera3D             camera;
    std::string          msg;
    size_t               ticks       = 0;
    bool                 camera_move = false;
    std::vector<Terrain> terrains;
    int                  terrains_width  = 10;
    int                  terrains_height = 10;
    int                  terrain_width   = 64;
    int                  terrain_height  = 64;
};

#endif
