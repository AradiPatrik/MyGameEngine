//
// Created by Patrik Aradi on 2023/12/22.
//

#ifndef MULTIPLELIGHTSHADERCUBE_H
#define MULTIPLELIGHTSHADERCUBE_H

#ifdef WIN32
#include <glad/glad.h>
#else
#include <OpenGL/gl3.h>
#endif
#include <glm/glm.hpp>
#include <vector>
#include "../engine/Shader.h"

namespace Engine {
class Texture;
class Camera;
class Shader;
}

class MultipleLightShaderCube {
public:
    MultipleLightShaderCube(const Engine::Texture& diffuseMap, const Engine::Texture& specularMap);

    void setPosition(const glm::vec3&);
    void setRotation(const glm::vec3&);
    void update(float deltaTime);
    void draw(const Engine::Shader& shader) const;

private:
    GLuint m_vao = 0;

    glm::vec3 m_position{};
    glm::vec3 m_rotation{};

    const Engine::Texture& m_diffuseMap;
    const Engine::Texture& m_specularMap;
};

#endif // MULTIPLELIGHTSHADERCUBE_H
