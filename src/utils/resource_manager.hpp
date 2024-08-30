#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <cstdint>
#include <vector>
#include <string>
#include <raylib.h>

class ResourceManager {
    public:
        Model load_model(std::string const& filename) {
            Model m = LoadModel(filename.c_str());
            m_models.push_back(m);
            return m;
        }

        Shader load_shader(std::string const& vs_path, std::string const& fs_path) {
            Shader s = LoadShader(vs_path.c_str(), fs_path.c_str());
            m_shaders.push_back(s);
            return s;
        }

    private:
        std::vector<Model> m_models;
        std::vector<Shader> m_shaders;
};

#endif


