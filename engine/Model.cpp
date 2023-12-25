//
// Created by Taipei Home on 12/23/2023.
//

#include "Model.h"

#include "Mesh.h"
#include "Texture.h"

#include <any>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
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
    m_directory = path.substr(0, path.find_last_of('/'));
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (const auto error = std::string(importer.GetErrorString()); !error.empty()) {
        throw std::runtime_error(error);
    }
    processNode(scene->mRootNode, scene);
}

void Engine::Model::processNode(const aiNode* node, const aiScene* scene) // NOLINT(*-no-recursion)
{
    std::cout << node->mName.C_Str() << std::endl;
    for (int i = 0; i < node->mNumMeshes; ++i) {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Engine::Mesh Engine::Model::processMesh(const aiMesh* mesh, const aiScene* scene) const
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

void Engine::Model::loadMaterialTextures(const aiMaterial* material, std::vector<Texture>& diffuseMaps, std::vector<Texture>& specularMaps) const
{
    for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, i, &str);
        std::string path = m_directory + '/' + str.C_Str();
        if (const auto texture = s_getLoadedTexture(path); texture != nullptr) {
            diffuseMaps.push_back(*texture);
            continue;
        }
        const auto texture = Texture(path);
        diffuseMaps.push_back(texture);
        s_loadedTextures.insert({path, texture});
    }

    for (int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); ++i) {
        aiString str;
        material->GetTexture(aiTextureType_SPECULAR, i, &str);
        std::string path = m_directory + '/' + str.C_Str();
        if (const auto texture = s_getLoadedTexture(path); texture != nullptr) {
            specularMaps.push_back(*texture);
            continue;
        }
        const auto texture = Texture(path);
        s_loadedTextures.insert({ path, texture });
        specularMaps.push_back(texture);
    }
}

std::unordered_map<std::string, Engine::Texture> Engine::Model::s_loadedTextures{};

const Engine::Texture* Engine::Model::s_getLoadedTexture(const std::string& path)
{
    const auto iterator = s_loadedTextures.find(path);
    if (iterator != s_loadedTextures.end()) {
        return &iterator->second;
    }

    return nullptr;
}
