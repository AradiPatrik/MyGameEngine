//
// Created by Patrik Aradi on 2023/12/6.
//

#ifndef LIGHTCUBE_H
#define LIGHTCUBE_H

#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PhongLightProperties.h"

class LightCube
{
public:
    LightCube(const PhongLightProperties& phongLightProperties);
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setPosition(const glm::vec3& newPosition);
    const glm::vec3 &getPosition() const;
    const PhongLightProperties &getLightProperties() const;
    void bindToShader(const Engine::Shader& shader) const;

private:
    GLuint vao;

    Engine::Shader shader;
    glm::vec3 position;

    PhongLightProperties phongLightProperties;
};


#endif //LIGHTCUBE_H
