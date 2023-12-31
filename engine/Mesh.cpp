//
// Created by Patrik Aradi on 2023/12/22.
//

#include "Mesh.h"

#include "Shader.h"
#include "Texture.h"

#ifndef WIN32
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

#include <utility>

namespace Engine {
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> diffuseMaps, std::vector<Texture> specularMaps)
    : m_vertices(std::move(vertices))
    , m_indices(std::move(indices))
    , m_diffuseMaps(std::move(diffuseMaps))
    , m_specularMaps(std::move(specularMaps))
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_vertices.size() * sizeof(Vertex)), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_indices.size() * sizeof(unsigned int)), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}
void Mesh::draw(const Shader& shader) const
{
    shader.use();
    glBindVertexArray(m_vao);

    int i = 0;
    // for (; i < m_diffuseMaps.size(); ++i) {
    //     m_diffuseMaps[i].bind(shader, GL_TEXTURE0 + i, "material.diffuseMaps[" + std::to_string(i) + "]");
    // }
    //
    // for (; i < m_specularMaps.size(); ++i) {
    //     m_specularMaps[i].bind(shader, GL_TEXTURE0 + i, "material.specularMaps[" + std::to_string(i) + "]");
    // }
    m_diffuseMaps[0].bind(shader, GL_TEXTURE0, "u_material.diffuse");
    m_specularMaps[0].bind(shader, GL_TEXTURE1, "u_material.specular");
    shader.setUniform("material.shininess", 32.0f);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
}
} // Engine