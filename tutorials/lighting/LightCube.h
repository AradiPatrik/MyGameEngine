//
// Created by Patrik Aradi on 2023/12/6.
//

#ifndef LIGHTCUBE_H
#define LIGHTCUBE_H

#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LightCube
{
public:
    LightCube();
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setPosition(const glm::vec3& newPosition);

private:
    GLuint vao;

    Engine::Shader shader;
    glm::vec3 position;
};


#endif //LIGHTCUBE_H
