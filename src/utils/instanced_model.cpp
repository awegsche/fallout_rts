#include "instanced_model.hpp"
#include "utils/renderer.hpp"

InstancedModel::InstancedModel(std::string const &filename, Renderer const &renderer)
    : model(LoadModel(filename.c_str()))
{
    instanced_model.meshMaterial  = new int[model.meshCount];
    instanced_model.materials     = new Material[model.materialCount];
    instanced_model.meshes        = new Mesh[model.meshCount];
    instanced_model.meshCount     = model.meshCount;
    instanced_model.materialCount = model.materialCount;
    instanced_model.transform     = model.transform;

    std::memcpy(instanced_model.meshMaterial, model.meshMaterial, model.meshCount * sizeof(int));
    std::memcpy(instanced_model.materials, model.materials, model.materialCount * sizeof(Material));
    std::memcpy(instanced_model.meshes, model.meshes, model.meshCount * sizeof(Mesh));

    for (int i = 0; i < model.materialCount; ++i) {
        model.materials[i].shader           = renderer.single_shader();
        instanced_model.materials[i].shader = renderer.instance_shader();
    }
}
