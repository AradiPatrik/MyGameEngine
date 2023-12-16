//
// Created by Patrik Aradi on 2023/12/15.
//

#ifndef MATERIALCUBE_H
#define MATERIALCUBE_H

#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Material;

namespace Engine
{
    class Camera;
}

class LightCube;

class MaterialCube {
public:
    MaterialCube(const glm::vec3& cubeColor, const glm::vec3& lightColor, const LightCube& light, const Engine::Camera& camera, const Material& material);
    void draw(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);
    void setPosition(const glm::vec3 &newPosition);

protected:
    GLuint vao;

    Engine::Shader shader;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cubeColor;
    glm::vec3 lightColor;
    const LightCube& light;
    const Engine::Camera& camera;
    const Material& material;
};



#endif //MATERIALCUBE_H
