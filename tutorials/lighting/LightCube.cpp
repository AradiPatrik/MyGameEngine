//
// Created by Patrik Aradi on 2023/12/6.
//

#include "LightCube.h"

#include "../../engine/MeshUtils.h"

LightCube::LightCube(const PhongLightProperties& lightProperties): shader("shaders/tutorial_lighting/light_cube/vertex.glsl",
                               "shaders/tutorial_lighting/light_cube/fragment.glsl"),
                        position(0, 0, 0),
                        vao(MeshUtils::createBoxVao()),
                        phongLightProperties(lightProperties)
{
}

void LightCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, position);
    MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
}

void LightCube::setPosition(const glm::vec3& newPosition)
{
    position = newPosition;
}

const glm::vec3& LightCube::getPosition() const
{
    return position;
}

const PhongLightProperties& LightCube::getLightProperties() const
{
    return phongLightProperties;
}

void LightCube::bindToShader(const Shader& shader) const
{
    shader.setUniform("u_lightPosition", position);
    shader.setUniform("u_light.ambient", phongLightProperties.ambient);
    shader.setUniform("u_light.diffuse", phongLightProperties.diffuse);
    shader.setUniform("u_light.specular", phongLightProperties.specular);
}
