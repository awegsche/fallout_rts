#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "rlights.h"
#include "utils/instanced_model.hpp"
#include <raylib.h>
#include <spdlog/spdlog.h>
#include <vector>

class Renderer
{
  public:
    Renderer()
    {
        spdlog::debug("Initializing renderer");
        m_instance_shader = LoadShader("shaders/lighting_instancing_vs.glsl", "shaders/lighting_fs.glsl");

        m_instance_shader.locs[SHADER_LOC_MATRIX_MVP]  = GetShaderLocation(m_instance_shader, "mvp");
        m_instance_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(m_instance_shader, "viewPos");
        m_instance_shader.locs[SHADER_LOC_MATRIX_MODEL] =
            GetShaderLocationAttrib(m_instance_shader, "instanceTransform");

        // Set m_instance_shader value: ambient light level
        int   ambientLoc = GetShaderLocation(m_instance_shader, "ambient");
        float amb[4]     = { 0.2f, 0.2f, 0.2f, 1.0f };
        SetShaderValue(m_instance_shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);
        UpdateLightValues(m_instance_shader, 0);

        CreateLight(LIGHT_DIRECTIONAL, { -1.0f, 1.0f, -1.0f }, {0.0f, 0.0f, 0.0f}, WHITE, m_instance_shader);

        // --
        m_single_shader   = LoadShader("shaders/lighting_single_vs.glsl", "shaders/lighting_fs.glsl");

        m_single_shader.locs[SHADER_LOC_MATRIX_MVP]  = GetShaderLocation(m_single_shader, "mvp");
        m_single_shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(m_single_shader, "viewPos");

        ambientLoc                                   = GetShaderLocation(m_single_shader, "ambient");
        SetShaderValue(m_single_shader, ambientLoc, &amb, SHADER_UNIFORM_VEC4);
        UpdateLightValues(m_single_shader, 0);

        spdlog::debug("Renderer initialized");
    }

    ~Renderer()
    {
        UnloadShader(m_instance_shader);
        UnloadShader(m_single_shader);
    }

    void reset_instances() { m_instance_transforms.clear(); }

    void push_instance_transform(Matrix m) { m_instance_transforms.push_back(m); }

    void draw_instances(InstancedModel const &instanced_model) const
    {
        Model const &model = instanced_model.instanced_model;

        for (int i = 0; i < model.meshCount; ++i) {
            DrawMeshInstanced(model.meshes[i],
                model.materials[model.meshMaterial[i]],
                m_instance_transforms.data(),
                m_instance_transforms.size());
        }
    }

    void draw_single_model(InstancedModel const &model, Vector3 position) const
    {
        DrawModel(model.model, position, 1.0f, WHITE);
    }

    [[nodiscard]] Shader instance_shader() const { return m_instance_shader; }

    [[nodiscard]] Shader single_shader() const { return m_single_shader; }

  private:
    Shader              m_instance_shader{};
    Shader              m_single_shader{};
    std::vector<Matrix> m_instance_transforms;
};

#endif
