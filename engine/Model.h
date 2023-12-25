//
// Created by Taipei Home on 12/23/2023.
//

#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "assimp/material.h"

#include <string>
#include <unordered_map>
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
    std::string m_directory;

    void loadModel(const std::string& path);
    void processNode(const aiNode*, const aiScene*);
    Mesh processMesh(const aiMesh*, const aiScene*) const;
    void loadMaterialTextures(const aiMaterial*, std::vector<Texture>& diffuseMaps, std::vector<Texture>& specularMaps) const;

    static std::unordered_map<std::string, Texture> s_loadedTextures;
    static const Texture* s_getLoadedTexture(const std::string& path);
};
}

#endif // MODEL_H
