//
// Created by Patrik Aradi on 2023/12/8.
//

#ifndef LITCUBE_H
#define LITCUBE_H


#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    class Camera;
}

class LightCube;

class LitCube {
public:
    LitCube(const glm::vec3& cubeColor, const glm::vec3& lightColor, const LightCube& light, const Engine::Camera& camera);
    void draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
    void setPosition(const glm::vec3 &newPosition);

protected:
    GLuint vao;

    Engine::Shader shader;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cubeColor;
    glm::vec3 lightColor;
    const LightCube& light;
    const Engine::Camera& camera;
};



#endif //LITCUBE_H
