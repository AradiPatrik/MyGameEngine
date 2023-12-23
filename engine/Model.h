//
// Created by Taipei Home on 12/23/2023.
//

#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

#include <string>
#include <vector>

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;
namespace Engine {
class Shader;
class Texture;
class Model {
public:
    explicit Model(const std::string& path);

    void draw(const Shader& shader) const;
private:
    std::vector<Mesh> m_meshes;

    void loadModel(const std::string& path);
    void processNode(const aiNode*, const aiScene*);
    Mesh processMesh(const aiMesh*, const aiScene*);
    void loadMaterialTextures(const aiMaterial*, std::vector<Texture>& diffuseMaps, std::vector<Texture>& specularMaps);
};
}

#endif // MODEL_H
