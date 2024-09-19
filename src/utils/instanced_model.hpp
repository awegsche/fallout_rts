#ifndef __INSTANCED_MODEL_H__
#define __INSTANCED_MODEL_H__

#include <raylib.h>
#include <string>
#include <vector>

class Renderer;

struct InstancedModel {
    InstancedModel(std::string const &filename, Renderer const &renderer);

    InstancedModel(InstancedModel const&) = delete;
    InstancedModel(InstancedModel &&) = delete;

    InstancedModel& operator=(InstancedModel const&) = delete;
    InstancedModel& operator=(InstancedModel &&) = delete;

    ~InstancedModel() {
        delete instanced_model.meshMaterial;
        delete instanced_model.materials;
        delete instanced_model.meshes;
    }

    Model model;
    Model instanced_model;

};

#endif
