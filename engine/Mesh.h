//
// Created by Patrik Aradi on 2023/12/22.
//

#ifndef MESH_H
#define MESH_H
#include "Texture.h"
#include "glm/glm.hpp"

#include <vector>

namespace Engine {
class Shader;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> diffuseMaps, std::vector<Texture> specularMaps);
    void draw(const Shader&) const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_diffuseMaps;
    std::vector<Texture> m_specularMaps;
    unsigned int m_vao{};
    unsigned int m_vbo{};
    unsigned int m_ebo{};
};
} // Engine

#endif // MESH_H
