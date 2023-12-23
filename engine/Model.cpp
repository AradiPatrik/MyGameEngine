//
// Created by Taipei Home on 12/23/2023.
//

#include "Model.h"

#include "Mesh.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stdexcept>

Engine::Model::Model(const std::string& path)
{
    loadModel(path);
}

void Engine::Model::draw(const Shader& shader) const
{
    for (const auto& mesh : m_meshes) {
        mesh.draw(shader);
    }
}

void Engine::Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (importer.GetErrorString()) {
        throw std::runtime_error(importer.GetErrorString());
    }
    processNode(scene->mRootNode, scene);
}

void Engine::Model::processNode(const aiNode* node, const aiScene* scene)
{
    for (int i = 0; i < node->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Engine::Mesh Engine::Model::processMesh(const aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> diffuseMaps;
    std::vector<Texture> specularMaps;

    for (int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex) {
        const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        loadMaterialTextures(material, diffuseMaps, specularMaps);
    }

    return { vertices, indices, diffuseMaps, specularMaps };
}

void Engine::Model::loadMaterialTextures(const aiMaterial* material, std::vector<Texture>& diffuseMaps, std::vector<Texture>& specularMaps)
{
    for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, i, &str);
        diffuseMaps.emplace_back(str.C_Str());
    }

    for (int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); ++i) {
        aiString str;
        material->GetTexture(aiTextureType_SPECULAR, i, &str);

        specularMaps.emplace_back(str.C_Str());
    }
}
