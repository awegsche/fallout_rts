#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <random>
#include <vector>

#include "rlights.h"
#include <raylib.h>
#include <rlgl.h>

class Chunk;

constexpr float GROUND_TILE_SIZE = 1.0f;

enum class TerrainType { Forest, Ruin, Plain };

struct TerrainCell
{
    TerrainType type;
    float       value;
    float       radiation;
};

struct TerrainModel
{
    TerrainModel() = default;

    TerrainModel(const std::string &filename, Shader shader)
    {
        model                     = LoadModel(filename.c_str());
        model.materials[0].shader = shader;
    }

    Model               model      = {};
    std::vector<Matrix> transforms = {};
};

struct TerrainManager
{
    TerrainManager()
    {

        shader = LoadShader(R"(shaders\lighting_instancing_vs.glsl)", R"(shaders\lighting_fs.glsl)");

        // Get shader locations
        shader.locs[SHADER_LOC_MATRIX_MVP]   = GetShaderLocation(shader, "mvp");
        shader.locs[SHADER_LOC_VECTOR_VIEW]  = GetShaderLocation(shader, "viewPos");
        shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader, "instanceTransform");

        // Set shader value: ambient light level
        int   ambientLoc = GetShaderLocation(shader, "ambient");
        float amb[4]     = { 0.3f, 0.25f, 0.2f, 1.0f };
        SetShaderValue(shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);

        tree01_model = TerrainModel(R"(assets\tree01.obj)", shader);
        tree02_model = TerrainModel(R"(assets\tree02.obj)", shader);

        CreateLight(LIGHT_DIRECTIONAL, { -1.0f, 1.0f, -1.0f }, {0.0f, 0.0f, 0.0f}, WHITE, shader);
    }

    ~TerrainManager()
    {
        UnloadModel(tree01_model.model);
        UnloadModel(tree02_model.model);
        UnloadShader(shader);
    }

    void draw_chunk(Chunk const &chunk);

    TerrainModel tree01_model;
    TerrainModel tree02_model;
    Shader       shader = {};
};

inline Light setup_light(Shader shader)
{
    return CreateLight(LIGHT_DIRECTIONAL, { 1.0f, 1.0f, 1.0f }, {0.0f, 0.0f, 0.0f}, WHITE, shader);
}
#endif
